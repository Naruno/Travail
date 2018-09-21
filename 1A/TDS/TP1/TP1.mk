##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=TP1
ConfigurationName      :=Debug
WorkspacePath          := "/home/nicolas/Documents/TDS"
ProjectPath            := "/home/nicolas/Documents/TDS/TP1"
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
ObjectsFileList        :="TP1.txt"
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
Objects0=$(IntermediateDirectory)/rendu_monnaie.c$(ObjectSuffix) $(IntermediateDirectory)/harmonique.c$(ObjectSuffix) $(IntermediateDirectory)/tris_entier.c$(ObjectSuffix) $(IntermediateDirectory)/Je_pense.c$(ObjectSuffix) $(IntermediateDirectory)/syracuse.c$(ObjectSuffix) $(IntermediateDirectory)/stars_matrix_like.c$(ObjectSuffix) $(IntermediateDirectory)/juste_prix.c$(ObjectSuffix) $(IntermediateDirectory)/rendu_monnaie2.c$(ObjectSuffix) 



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
$(IntermediateDirectory)/rendu_monnaie.c$(ObjectSuffix): rendu_monnaie.c $(IntermediateDirectory)/rendu_monnaie.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/nicolas/Documents/TDS/TP1/rendu_monnaie.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/rendu_monnaie.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/rendu_monnaie.c$(DependSuffix): rendu_monnaie.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/rendu_monnaie.c$(ObjectSuffix) -MF$(IntermediateDirectory)/rendu_monnaie.c$(DependSuffix) -MM "rendu_monnaie.c"

$(IntermediateDirectory)/rendu_monnaie.c$(PreprocessSuffix): rendu_monnaie.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/rendu_monnaie.c$(PreprocessSuffix) "rendu_monnaie.c"

$(IntermediateDirectory)/harmonique.c$(ObjectSuffix): harmonique.c $(IntermediateDirectory)/harmonique.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/nicolas/Documents/TDS/TP1/harmonique.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/harmonique.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/harmonique.c$(DependSuffix): harmonique.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/harmonique.c$(ObjectSuffix) -MF$(IntermediateDirectory)/harmonique.c$(DependSuffix) -MM "harmonique.c"

$(IntermediateDirectory)/harmonique.c$(PreprocessSuffix): harmonique.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/harmonique.c$(PreprocessSuffix) "harmonique.c"

$(IntermediateDirectory)/tris_entier.c$(ObjectSuffix): tris_entier.c $(IntermediateDirectory)/tris_entier.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/nicolas/Documents/TDS/TP1/tris_entier.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/tris_entier.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tris_entier.c$(DependSuffix): tris_entier.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/tris_entier.c$(ObjectSuffix) -MF$(IntermediateDirectory)/tris_entier.c$(DependSuffix) -MM "tris_entier.c"

$(IntermediateDirectory)/tris_entier.c$(PreprocessSuffix): tris_entier.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/tris_entier.c$(PreprocessSuffix) "tris_entier.c"

$(IntermediateDirectory)/Je_pense.c$(ObjectSuffix): Je_pense.c $(IntermediateDirectory)/Je_pense.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/nicolas/Documents/TDS/TP1/Je_pense.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Je_pense.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Je_pense.c$(DependSuffix): Je_pense.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Je_pense.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Je_pense.c$(DependSuffix) -MM "Je_pense.c"

$(IntermediateDirectory)/Je_pense.c$(PreprocessSuffix): Je_pense.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Je_pense.c$(PreprocessSuffix) "Je_pense.c"

$(IntermediateDirectory)/syracuse.c$(ObjectSuffix): syracuse.c $(IntermediateDirectory)/syracuse.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/nicolas/Documents/TDS/TP1/syracuse.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/syracuse.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/syracuse.c$(DependSuffix): syracuse.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/syracuse.c$(ObjectSuffix) -MF$(IntermediateDirectory)/syracuse.c$(DependSuffix) -MM "syracuse.c"

$(IntermediateDirectory)/syracuse.c$(PreprocessSuffix): syracuse.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/syracuse.c$(PreprocessSuffix) "syracuse.c"

$(IntermediateDirectory)/stars_matrix_like.c$(ObjectSuffix): stars_matrix_like.c $(IntermediateDirectory)/stars_matrix_like.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/nicolas/Documents/TDS/TP1/stars_matrix_like.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/stars_matrix_like.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/stars_matrix_like.c$(DependSuffix): stars_matrix_like.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/stars_matrix_like.c$(ObjectSuffix) -MF$(IntermediateDirectory)/stars_matrix_like.c$(DependSuffix) -MM "stars_matrix_like.c"

$(IntermediateDirectory)/stars_matrix_like.c$(PreprocessSuffix): stars_matrix_like.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/stars_matrix_like.c$(PreprocessSuffix) "stars_matrix_like.c"

$(IntermediateDirectory)/juste_prix.c$(ObjectSuffix): juste_prix.c $(IntermediateDirectory)/juste_prix.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/nicolas/Documents/TDS/TP1/juste_prix.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/juste_prix.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/juste_prix.c$(DependSuffix): juste_prix.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/juste_prix.c$(ObjectSuffix) -MF$(IntermediateDirectory)/juste_prix.c$(DependSuffix) -MM "juste_prix.c"

$(IntermediateDirectory)/juste_prix.c$(PreprocessSuffix): juste_prix.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/juste_prix.c$(PreprocessSuffix) "juste_prix.c"

$(IntermediateDirectory)/rendu_monnaie2.c$(ObjectSuffix): rendu_monnaie2.c $(IntermediateDirectory)/rendu_monnaie2.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/nicolas/Documents/TDS/TP1/rendu_monnaie2.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/rendu_monnaie2.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/rendu_monnaie2.c$(DependSuffix): rendu_monnaie2.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/rendu_monnaie2.c$(ObjectSuffix) -MF$(IntermediateDirectory)/rendu_monnaie2.c$(DependSuffix) -MM "rendu_monnaie2.c"

$(IntermediateDirectory)/rendu_monnaie2.c$(PreprocessSuffix): rendu_monnaie2.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/rendu_monnaie2.c$(PreprocessSuffix) "rendu_monnaie2.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


