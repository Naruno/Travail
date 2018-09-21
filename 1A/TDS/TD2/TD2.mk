##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=TD2
ConfigurationName      :=Debug
WorkspacePath          := "/home/nicolas/Documents/TDS"
ProjectPath            := "/home/nicolas/Documents/TDS/TD2"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Nicolas
Date                   :=02/10/17
CodeLitePath           :="/home/nicolas/.codelite"
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="TD2.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/exponentielle.c$(ObjectSuffix) $(IntermediateDirectory)/permute1.c$(ObjectSuffix) $(IntermediateDirectory)/permute2.c$(ObjectSuffix) $(IntermediateDirectory)/permute3.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/exponentielle.c$(ObjectSuffix): exponentielle.c $(IntermediateDirectory)/exponentielle.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/nicolas/Documents/TDS/TD2/exponentielle.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/exponentielle.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/exponentielle.c$(DependSuffix): exponentielle.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/exponentielle.c$(ObjectSuffix) -MF$(IntermediateDirectory)/exponentielle.c$(DependSuffix) -MM "exponentielle.c"

$(IntermediateDirectory)/exponentielle.c$(PreprocessSuffix): exponentielle.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/exponentielle.c$(PreprocessSuffix) "exponentielle.c"

$(IntermediateDirectory)/permute1.c$(ObjectSuffix): permute1.c $(IntermediateDirectory)/permute1.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/nicolas/Documents/TDS/TD2/permute1.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/permute1.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/permute1.c$(DependSuffix): permute1.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/permute1.c$(ObjectSuffix) -MF$(IntermediateDirectory)/permute1.c$(DependSuffix) -MM "permute1.c"

$(IntermediateDirectory)/permute1.c$(PreprocessSuffix): permute1.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/permute1.c$(PreprocessSuffix) "permute1.c"

$(IntermediateDirectory)/permute2.c$(ObjectSuffix): permute2.c $(IntermediateDirectory)/permute2.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/nicolas/Documents/TDS/TD2/permute2.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/permute2.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/permute2.c$(DependSuffix): permute2.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/permute2.c$(ObjectSuffix) -MF$(IntermediateDirectory)/permute2.c$(DependSuffix) -MM "permute2.c"

$(IntermediateDirectory)/permute2.c$(PreprocessSuffix): permute2.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/permute2.c$(PreprocessSuffix) "permute2.c"

$(IntermediateDirectory)/permute3.c$(ObjectSuffix): permute3.c $(IntermediateDirectory)/permute3.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/nicolas/Documents/TDS/TD2/permute3.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/permute3.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/permute3.c$(DependSuffix): permute3.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/permute3.c$(ObjectSuffix) -MF$(IntermediateDirectory)/permute3.c$(DependSuffix) -MM "permute3.c"

$(IntermediateDirectory)/permute3.c$(PreprocessSuffix): permute3.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/permute3.c$(PreprocessSuffix) "permute3.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


