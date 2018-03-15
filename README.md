# Crossword
This project is about to solve a square crossword with a given grid (Crossword1.txt, etc) and a given dictionary (Words.txt, 
MoreWords.txt, etc). The grid file contains the size of the crossword and the positions of the black cells. The dictionary file
contains the available words to fill the crossword, one at each line. As output, the program prints the words that solve the 
dictionary one at each line, unless the user gives -check. <br />
Execution command: ./crossword < gridFile > {-dict < dictionaryFile > } {-check} {-draw}
* -dict <dictionaryFile> is an optional argument. If it's not given, default dictionary is Words.txt 
* -check is an optional argument and it checks whether the given words solve the dictionary or not<br />
  Possible mistakes:
  * More words than needed
  * Word not in dictionary
  * Word cannot be placed
  * Not enough words
* -draw is an optional arguments and if you pick it, crossword will be drawn
