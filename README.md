# Aliteria-Updated
updated base of Aliteria click on the vcxproj twice and open with visual studio and now u have an sln file injector crashes after 10 mins put the dll next to Injector.exe name it Module.dll run roblox then the Injector and try executing and it will work

# CRASHES
if you crash while injecting its the windows issue because windows 11 doesnt support this injector so try and get another injector that works on windows 11 that injector only works for 10

# IMPORTANT
injector wont get created when u build as its not in the vcxproj include it in project as an console app so just use the injector.exe directly as its same code as main.cpp if your lazy.

Go to dependencies folder and Extract the Luau zip to folder called "Luau" or else you'll get errors.

# EXECUTE CODE [winforms .net framework]

    using System.Net.Sockets;
    private void button1_Click(object sender, EventArgs e)
    {
        
       try
            {
                using (TcpClient Client = new TcpClient("127.0.0.1", 6969))
                using (NetworkStream Stream = Client.GetStream())
                {
                    byte[] ScriptBytes = Encoding.UTF8.GetBytes(ScriptEditor.Text);
                    int ScriptLength = ScriptBytes.Length;

                    byte[] LengthBytes = BitConverter.GetBytes(ScriptLength);
                    if (BitConverter.IsLittleEndian)
                        Array.Reverse(LengthBytes);

                    Stream.Write(LengthBytes, 0, 4);
                    Stream.Write(ScriptBytes, 0, ScriptBytes.Length);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Failed to Execute script: " + ex.Message, "Aliteria", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }
  
