##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=TD3
ConfigurationName      :=Debug
WorkspacePath          := "/home/nicolas/Documents/TDS"
ProjectPath            := "/home/nicolas/Documents/TDS/TD3"
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
ObjectsFileList        :="TD3.txt"
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
Objects0=$(IntermediateDirectory)/conditionnelle_if.c$(ObjectSuffix) $(IntermediateDirectory)/conditionnelle_switch.c$(ObjectSuffix) $(IntermediateDirectory)/un_peu_de_code_cercle.c$(ObjectSuffix) $(IntermediateDirectory)/compregension.c$(ObjectSuffix) $(IntermediateDirectory)/erreur_de_code.c$(ObjectSuffix) $(IntermediateDirectory)/Du_code_du_code.c$(ObjectSuffix) $(IntermediateDirectory)/Du_code_du_code2.c$(ObjectSuffix) $(IntermediateDirectory)/scanf_charriot.c$(ObjectSuffix) 



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
$(IntermediateDirectory)/conditionnelle_if.c$(ObjectSuffix): conditionnelle_if.c $(IntermediateDirectory)/conditionnelle_if.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/nicolas/Documents/TDS/TD3/conditionnelle_if.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/conditionnelle_if.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/conditionnelle_if.c$(DependSuffix): conditionnelle_if.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/conditionnelle_if.c$(ObjectSuffix) -MF$(IntermediateDirectory)/conditionnelle_if.c$(DependSuffix) -MM "conditionnelle_if.c"

$(IntermediateDirectory)/conditionnelle_if.c$(PreprocessSuffix): conditionnelle_if.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/conditionnelle_if.c$(PreprocessSuffix) "conditionnelle_if.c"

$(IntermediateDirectory)/conditionnelle_switch.c$(ObjectSuffix): conditionnelle_switch.c $(IntermediateDirectory)/conditionnelle_switch.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/nicolas/Documents/TDS/TD3/conditionnelle_switch.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/conditionnelle_switch.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/conditionnelle_switch.c$(DependSuffix): conditionnelle_switch.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/conditionnelle_switch.c$(ObjectSuffix) -MF$(IntermediateDirectory)/conditionnelle_switch.c$(DependSuffix) -MM "conditionnelle_switch.c"

$(IntermediateDirectory)/conditionnelle_switch.c$(PreprocessSuffix): conditionnelle_switch.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/conditionnelle_switch.c$(PreprocessSuffix) "conditionnelle_switch.c"

$(IntermediateDirectory)/un_peu_de_code_cercle.c$(ObjectSuffix): un_peu_de_code_cercle.c $(IntermediateDirectory)/un_peu_de_code_cercle.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/nicolas/Documents/TDS/TD3/un_peu_de_code_cercle.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/un_peu_de_code_cercle.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/un_peu_de_code_cercle.c$(DependSuffix): un_peu_de_code_cercle.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/un_peu_de_code_cercle.c$(ObjectSuffix) -MF$(IntermediateDirectory)/un_peu_de_code_cercle.c$(DependSuffix) -MM "un_peu_de_code_cercle.c"

$(IntermediateDirectory)/un_peu_de_code_cercle.c$(PreprocessSuffix): un_peu_de_code_cercle.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/un_peu_de_code_cercle.c$(PreprocessSuffix) "un_peu_de_code_cercle.c"

$(IntermediateDirectory)/compregension.c$(ObjectSuffix): compregension.c $(IntermediateDirectory)/compregension.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/nicolas/Documents/TDS/TD3/compregension.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/compregension.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/compregension.c$(DependSuffix): compregension.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/compregension.c$(ObjectSuffix) -MF$(IntermediateDirectory)/compregension.c$(DependSuffix) -MM "compregension.c"

$(IntermediateDirectory)/compregension.c$(PreprocessSuffix): compregension.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/compregension.c$(PreprocessSuffix) "compregension.c"

$(IntermediateDirectory)/erreur_de_code.c$(ObjectSuffix): erreur_de_code.c $(IntermediateDirectory)/erreur_de_code.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/nicolas/Documents/TDS/TD3/erreur_de_code.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/erreur_de_code.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/erreur_de_code.c$(DependSuffix): erreur_de_code.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/erreur_de_code.c$(ObjectSuffix) -MF$(IntermediateDirectory)/erreur_de_code.c$(DependSuffix) -MM "erreur_de_code.c"

$(IntermediateDirectory)/erreur_de_code.c$(PreprocessSuffix): erreur_de_code.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/erreur_de_code.c$(PreprocessSuffix) "erreur_de_code.c"

$(IntermediateDirectory)/Du_code_du_code.c$(ObjectSuffix): Du_code_du_code.c $(IntermediateDirectory)/Du_code_du_code.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/nicolas/Documents/TDS/TD3/Du_code_du_code.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Du_code_du_code.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Du_code_du_code.c$(DependSuffix): Du_code_du_code.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Du_code_du_code.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Du_code_du_code.c$(DependSuffix) -MM "Du_code_du_code.c"

$(IntermediateDirectory)/Du_code_du_code.c$(PreprocessSuffix): Du_code_du_code.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Du_code_du_code.c$(PreprocessSuffix) "Du_code_du_code.c"

$(IntermediateDirectory)/Du_code_du_code2.c$(ObjectSuffix): Du_code_du_code2.c $(IntermediateDirectory)/Du_code_du_code2.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/nicolas/Documents/TDS/TD3/Du_code_du_code2.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Du_code_du_code2.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Du_code_du_code2.c$(DependSuffix): Du_code_du_code2.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Du_code_du_code2.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Du_code_du_code2.c$(DependSuffix) -MM "Du_code_du_code2.c"

$(IntermediateDirectory)/Du_code_du_code2.c$(PreprocessSuffix): Du_code_du_code2.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Du_code_du_code2.c$(PreprocessSuffix) "Du_code_du_code2.c"

$(IntermediateDirectory)/scanf_charriot.c$(ObjectSuffix): scanf_charriot.c $(IntermediateDirectory)/scanf_charriot.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/nicolas/Documents/TDS/TD3/scanf_charriot.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/scanf_charriot.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/scanf_charriot.c$(DependSuffix): scanf_charriot.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/scanf_charriot.c$(ObjectSuffix) -MF$(IntermediateDirectory)/scanf_charriot.c$(DependSuffix) -MM "scanf_charriot.c"

$(IntermediateDirectory)/scanf_charriot.c$(PreprocessSuffix): scanf_charriot.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/scanf_charriot.c$(PreprocessSuffix) "scanf_charriot.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


