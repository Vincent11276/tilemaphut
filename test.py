from dataclasses import dataclass
import tkinter 

root = tkinter.Tk()
root.title("Ram Explorer")
root.geometry("1024x720")
root.minsize(1024, 720)
#root.iconbitmap("path")

list = tkinter.Listbox(root, font=("Courrier", 25)) 

@dataclass
class Meta:
    size: int
    type: str
    name: str
    ext: str
    
class File:
    def __init__(self):
        self.data = ""
        self.meta_data = Meta(0,None,None,None)
    def Read(self):
        return self.data
        
    def Write(self, NewData):
        self.data = str(NewData)
        
    def Append(self, AppendData):
        self.data += str(AppendData)
    
    
FilesList = []
CurrentDir = "/"
Dirs = []

def Actualize(Dir):
    CurrentDir = Dir
    for i in range(len(FilesList)): # up to 5
        list.insert(i, ":   " + str(FilesList[i].Metadata.name) + "." + str(FilesList[i].Metadata.ext))
        print( str(i) + ", " + FilesList[i].Metadata.name)
    list.pack(expand=1, fill=tkinter.BOTH)

def NewFile(Name, extention):
    Newfile = File()
    Newfile.Metadata = Meta(0, "File", CurrentDir + str(Name), str(extention))
    print(Newfile.Metadata.name)
    FilesList.append(Newfile)
    for i in range(len(FilesList)):
        print( str(i) + ", " + FilesList[i].Metadata.name)

def NewDir(Name):
    Newdir = File
    Newdir.Metadata = Meta(0, "Directory", CurrentDir + str(Name), None)
    FilesList.append(Newdir)


    
    

NewFile("Hello1", "txt")
NewFile("Hello2", "txt")
NewFile("Hello3", "txt")
NewFile("Hello4", "txt")
NewFile("Hello5", "txt")
#NewDir("THIS IS A DIR")
Actualize("/")
#print(dir(tkinter.Listbox()))
root.mainloop()