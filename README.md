Aliteria-Updated
updated base of Aliteria click on the vcxproj twice and open with visual studio and now u have an sln file injector crashes after 10 mins put the dll next to Injector.exe name it Module.dll run roblox then the Injector and try executing and it will work

CRASHES
if you crash while injecting its the windows issue because windows 11 doesnt support this injector so try and get another injector that works on windows 11 that injector only works for 10

IMPORTANT
injector wont get created when u build as its not in the vcxproj include it in project as an console app so just use the injector.exe directly as its same code as main.cpp if your lazy.

Go to dependencies folder and Extract the Luau zip to folder called "Luau" or else you'll get errors.

EXECUTE CODE [winforms .net framwowrk]
public partial class Form1 : Form
{
    
    private readonly string targetFilePath = Path.Combine(
        Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData),
        "taskscheduler.txt"
    );


    private void button1_Click(object sender, EventArgs e)
    {
        
        string scriptText = ScriptTextEditor.Text;

        if (string.IsNullOrWhiteSpace(scriptText))
        {
            MessageBox.Show("Please enter a script to execute.", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            return;
        }

        try
        {
  
            File.WriteAllText(targetFilePath, scriptText);
        }
        catch (IOException ex)
        {
          
            MessageBox.Show($"Failed to pipe execution script: {ex.Message}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
}
