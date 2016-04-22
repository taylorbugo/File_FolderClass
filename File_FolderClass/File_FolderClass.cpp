// File_FolderClass.cpp : Defines the entry point for the console application.


/*I believe that the overall structure is far more complex than it should be. If I was to revisit this example I would rewrite the class in a simpler way
such that it would use maps instead of pointers, this would prevent the use of the same name in a location which is not something I enforce.
In my implementation it is actually possible for files and folders to have the same name, I even check for it explicitly. I would also not normally make all
the members public, but for simplicity I have.*/

#include "stdafx.h"

using namespace std;


class File {
public:
	string content;
	string Name;

	//default constructor
	File()
	{
		Name = "";
		content = "";
	}

	//overridden constructor
	File(string Label)
	{
		Name = Label;
		content = "";
	}

	//copy constructor
	File(const File &Base)
	{
		Name = Base.Name;
		content = Base.content;
	}

	//copy constructor from a pointer
	File(const File* Base)
	{
		Name = Base->Name;
		content = Base->content;
	}

	void Display()
	{
		cout << content << endl;
	}
};



class Folder {
public:
	string Name;
	Folder* Folders;
	int num_Folders;
	File* Files;
	int num_Files;

	//default constructor
	Folder()
	{
		Name = "";
		Folders = nullptr;
		num_Folders = 0;
		Files = nullptr;
		num_Files = 0;
	}


	/* This destructor does not work properly, I believe it has to do with the way in which I have linked Files and Folders and their recursive nature
	Unfortunately this leaves a memory leak in my program which makes it unsafe to use. The destructor is called during the Folder.add() function which 
	shows the issue. I believe that it is caused by the destructor call made when one of the Folders assigned by copy is removed from scope.
	
	~Folder()
	{
		delete[] Files;
		delete[] Folders;
	}*/

	//overridden constructor
	Folder(string Label)
	{
		Name = Label;
		Folders = nullptr;
		num_Folders = 0;
		Files = nullptr;
		num_Files = 0;
	}

	//copy constructor
	Folder(const Folder &Base)
	{
		Name = Base.Name;
		num_Folders = Base.num_Folders;
		if ((num_Folders > 0) && (Base.Folders != nullptr))
		{
			Folders = new Folder[num_Folders];
			for (int index = 0; index < num_Folders; index++)
			{
				Folders[index] = Base.Folders[index];
			}
		}
		else
		{
			Folders = nullptr;
		}
		num_Files = Base.num_Files;
		if ((num_Files > 0) && (Base.Files != nullptr))
		{
			Files = new File[num_Files];
			for (int location = 0; location < num_Files; location++)
			{
				Files[location] = Base.Files[location];
			}
		}
		else
		{
			Files = nullptr;
		}
	}

	//copy constructor from a pointer
	Folder(const Folder* Base)
	{
		Name = Base->Name;
		num_Folders = Base->num_Folders;
		if ((num_Folders > 0) && (Base->Folders != nullptr))
		{
			Folders = new Folder[num_Folders];
			for (int index = 0; index < num_Folders; index++)
			{
				Folders[index] = Base->Folders[index];
			}
		}
		else
		{
			Folders = nullptr;
		}
		num_Files = Base->num_Files;
		if ((num_Files > 0) && (Base->Files != nullptr))
		{
			Files = new File[num_Files];
			for (int location = 0; location < num_Files; location++)
			{
				Files[location] = Base->Files[location];
			}
		}
		else
		{
			Files = nullptr;
		}
	}

	void Add(File Child)
	{
		if (num_Files > 0)
		{
			File* storage = new File[num_Files+1];
			for (int index = 0; index < num_Files; index++)
			{
				storage[index] = Files[index];
			}
			delete[] Files;
			Files = storage;
		}
		else
		{
			Files = new File[1];
		}
		Files[num_Files] = new File(Child);
		num_Files++;
	}

	void Add(Folder Child)
	{
		if (num_Folders > 0)
		{
			Folder* storage = new Folder[num_Folders + 1];
			for (int index = 0; index < num_Folders; index++)
			{
				storage[index] = Folders[index];
			}
			delete[] Folders;
			Folders = storage;
		}
		else
		{
			Folders = new Folder[1];
		}
		Folders[num_Folders] = new Folder(Child);
		num_Folders++;
	}

	//Will delete all files and folders containted within targeted folders recursively, targets are identified by Name property
	//since system allows for folders and files to contain the same name, this will remove all instances matching target string
	void DeleteFolder(string Search)
	{
		int targets = 0;
		for (int location = 0; location < num_Folders; location++)
		{
			if (Folders[location].Name == Search)
			{
				targets++;
			}
		}
		if ((targets > 0) && (targets < num_Folders))
		{
			Folder* storage = new Folder[num_Folders - targets];
			int offset = 0;
			for (int spot = 0; spot < num_Folders; spot++)
			{
				if (Folders[spot].Name != Search)
				{
					storage[spot - offset] = Folders[spot];
				}
				else
				{
					offset++;
				}
			}
			for (int index = 0; index < num_Folders; index++)
			{
				if (Folders[index].Name == Search)
				{
					for (int place = 0; place < Folders[index].num_Files; place++)
					{
						Folders[index].DeleteFile(Folders[index].Files[place].Name);
					}
					for (int position = 0; position < num_Folders; position++)
					{
						Folders[index].DeleteFolder(Folders[index].Folders[position].Name);
					}
				}
			}
			delete[] Folders;
			Folders = storage;
			num_Folders -= targets;
		}
		else if ((targets == num_Folders) && (num_Folders != 0))
		{
			delete[] Folders;
			num_Folders = 0;
		}
	}

	//Will delete all files matching target string
	//since system allows for files to contain the same name, this will remove all instances matching target string
	void DeleteFile(string Search)
	{
		int targets = 0;
		for (int index = 0; index < num_Files; index++)
		{
			if (Files[index].Name == Search)
			{
				targets++;
			}
		}
		if ((targets > 0) && (targets < num_Files))
		{
			File* storage = new File[num_Files - targets];
			int offset = 0;
			for (int spot = 0; spot < num_Files; spot++)
			{
				if (Files[spot].Name != Search)
				{
					storage[spot - offset] = Files[spot];
				}
				else
				{
					offset++;
				}
			}
			delete[] Files;
			Files = storage;
			num_Files -= targets;
		}
		else if ((targets == num_Files) && (num_Files != 0))
		{
			delete[] Files;
			num_Files = 0;
		}
	}

	//will display all names recursively, files and folders
	void Display()
	{
		cout << Name << endl;
		for (int position = 0; position < num_Files; position++)
		{
			cout << Files[position].Name << endl;
		}
		for (int index = 0; index < num_Folders; index++)
		{
			Folders[index].Display();
		}
	}

};



int main()
{
	Folder Grandparent = new Folder("Grandparent");
	Folder Parent = new Folder("Parent");
	File ChildA = new File("ChildA");
	ChildA.content = "This is the content for Child A";
	File ChildB = new File("ChildB");
	Folder ChildC = new Folder("ChildC");
	File GrandChild = new File("GrandChild");
	ChildC.Add(GrandChild);
	Parent.Add(ChildA);
	Parent.Add(ChildB);
	Parent.Add(ChildC);
	Grandparent.Add(Parent);
	Grandparent.Display();
	ChildA.Display();
	return 0;
}