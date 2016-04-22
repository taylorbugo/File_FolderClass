# File_FolderClass
File\Folder Class structure coding example.

Built using Visual Studio Community 2015

File/Folder Class structure

Create a simple set of object­oriented classes that represent a file­folder­ like system, where  folders and files can be:   
a. added
b. deleted
c. report their name as well as the name of their children, and their children’s children

For example, the Main function that uses the program might have the following code snippet in  it’s Main() that uses these classes:

Folder Grandparent = new Folder(“Grandparent”);  
Folder Parent = new Folder(“Parent”);  
File ChildA = new File(“ChildA”);  
ChildA.content = “This is the content for Child A”;  File ChildB = new File(“ChildB”);  
Folder ChildC = new Folder(“ChildC”);    File GrandChild = new File(“GrandChild”); 
ChildC.Add(GrandChild”);  
Parent.Add(ChildA);  
Parent.Add(ChildB);  
Parent.Add(ChildC);  
Grandparent.Add(Parent);  
Grandparent.Display();  
ChildA.Display();    

And, in this example, would produce on a console output (or similar to):    

Grandparent  
Parent  
ChildA  
ChildB  
ChildC  
GrandChild  
This is the content for Child A
