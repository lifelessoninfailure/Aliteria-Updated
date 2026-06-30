#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include <vector>
#include <thread>
#include "../Misc/Misc.h"
#include "../Aliteria_Main/Execution/Execution.h"
#include "../Aliteria_Main/Shared/Instances.h"

#pragma comment(lib, "ws2_32.lib")

namespace Communication
{
    inline bool ReadExactSocket( SOCKET Socket , void* Buffer , size_t Size )
    {
        size_t Total = 0;
        char* Out = static_cast< char* >( Buffer );
        while ( Total < Size )
        {
            int Received = recv( Socket , Out + Total , static_cast< int >( Size - Total ) , 0 );
            if ( Received <= 0 )
                return false;
            Total += static_cast< size_t >( Received );
        }
        return true;
    }

    inline void TcpServer( )
    {
        WSADATA Wsa;
        if ( WSAStartup( MAKEWORD( 2 , 2 ) , &Wsa ) != 0 )
            return;

        addrinfo Hints{};
        addrinfo* Result = nullptr;

        Hints.ai_family = AF_INET;
        Hints.ai_socktype = SOCK_STREAM;
        Hints.ai_protocol = IPPROTO_TCP;
        Hints.ai_flags = AI_PASSIVE;

        if ( getaddrinfo( "127.0.0.1" , "6969" , &Hints , &Result ) != 0 )
        {
            WSACleanup( );
            return;
        }

        SOCKET ListenSocket = socket( Result->ai_family , Result->ai_socktype , Result->ai_protocol );
        if ( ListenSocket == INVALID_SOCKET )
        {
            freeaddrinfo( Result );
            WSACleanup( );
            return;
        }

        BOOL Opt = TRUE;
        setsockopt( ListenSocket , SOL_SOCKET , SO_REUSEADDR , reinterpret_cast< const char* >( &Opt ) , sizeof( Opt ) );
        if ( bind( ListenSocket , Result->ai_addr , static_cast< int >( Result->ai_addrlen ) ) == SOCKET_ERROR )
        {
            closesocket( ListenSocket );
            freeaddrinfo( Result );
            WSACleanup( );
            return;
        }

        freeaddrinfo( Result );
        if ( listen( ListenSocket , SOMAXCONN ) == SOCKET_ERROR )
        {
            closesocket( ListenSocket );
            WSACleanup( );
            return;
        }

        Misc::Print( "Aliteria: Communication Started at 127.0.0.1:6969" );

        while ( true )
        {
            SOCKET ClientSocket = accept( ListenSocket , nullptr , nullptr );
            if ( ClientSocket == INVALID_SOCKET )
            {
                Sleep( 100 );
                continue;
            }

            uint32_t NetLen = 0;
            if ( !ReadExactSocket( ClientSocket , &NetLen , sizeof( NetLen ) ) )
            {
                closesocket( ClientSocket );
                continue;
            }

            uint32_t ScriptLen = ntohl( NetLen );
            if ( ScriptLen == 0 || ScriptLen > ( 8 * 1024 * 1024 ) )
            {
                closesocket( ClientSocket );
                continue;
            }

            std::vector< char > Buffer( ScriptLen );
            if ( !ReadExactSocket( ClientSocket , Buffer.data( ) , ScriptLen ) )
            {
                closesocket( ClientSocket );
                continue;
            }

            std::string Script( Buffer.data( ) , Buffer.size( ) );
            Execution::Execute( Shared::AliteriaState , Script );

            closesocket( ClientSocket );
        }

        closesocket( ListenSocket );
        WSACleanup( );
    }

    inline void Start( )
    {
        std::thread( TcpServer ).detach( );
    }
}
