# save format spec
this is the current spec for v0.0.0 of the algomusic save format and input for the audio generator

the save format is currently a folder structure, where in the root you have a data.txt file containing general metadata about the song such as artist name, along with data about the other files

the current folder structure is
root
| data.txt
| sequances
| | [sequance name].txt
| algorithms
| | [algorithm name].txt

in the future other subdirectories like one for samples might be added

this is very subject to change

## data.txt
this file contains general metadata about the project/song, this file is at the root of the project directory

the structure of this file is:

Artist: "[artist name]"
Last updated: "[date yyyy-mm-dd]"

Sequances:
[sequance file name].txt
[sequance 2 file name].txt
(basicly just a list of file names of sequances in the sequances directory)
end

Algorithms:
[algorithm file name].txt
[algorithm 2 file name].txt
(basicly just a list of file names of algorithms in the algorithms directory)
end

## sequance files
sequance files contain instructions for how algomusic should produce the initial envolopes to then send into the algorithms, these files contain things like notes, bpm setters, what algorithms to use and other functions relating to the sequancing of your music

all sequance files are read throgh at the same time, so if you want one sequance to start after another one you would need to program an initial delay on the one you want after

you need to have the first instruction set the bpm as the program wont know how fast to read the file otherwise, the timing of things is done on a row by row basis, so 3 NOTE keywords with a newline between would come out as pressing said note on a keyboard at the set bpm 3 times

the current list of keywords are:
NOTE [value], this adds a note at the current line, the value feild is a float representing the value of the note, for example 1 might be A on a keyboard, how this gets interperted is up to the algorithms you have made
NOOP, this is an instruction that does absolutly nothing, this is for pauses in your song
BPM [value], this sets the bpm at witch algomusic reads each preceding line

this will be masivly expanded as I add more features, for example setting the algorithms used and potentialy more sophisticated things like polyrythms via subsequances

by comma seperating instructions you can have multiple instructions happen during the same beat, this is usefull if you want to change the bpm at the same time as you have a note for example

## algorithm files
this is currently not in scope and all sequances run on one hardcoded algorithm
