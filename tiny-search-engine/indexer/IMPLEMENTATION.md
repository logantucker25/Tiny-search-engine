# implimentation spec for indexer.c

# logan Tucker, Oct 2022
# cs50

# Main
collects the page directory and index filen path names
page directopry is a crawler produced dir of webpage info and the index file will be where we write out the info from the idnex we build from those webpages

calls parse args to make sure arguments provides are accurate
calls index build and builds an index from webpage info
calls index save and saves index content into a text file
calls index delete to free memory

# parse args
confirms
-three args received
-arg1 is a valid crawler prodcuced web page directory calls validate function that searches for a /.crawler file in directory
-arg2 in file that can we written to

# index build
creates index in memory
craetes webpage data types from the files in web page directory
takes each individual page and sends them to index page function that inputs the webpages contents into the index datat type
deletes each web page after it is indexed

# index page
reads each word on a given webpage useing built in webpage_getnextword func
adds all words over 3 letters in length to the index
-takes word check if its in the index, if it isnt add it then incriment its value either way
free the word at the end

# counters delete
function that deletes counters, pass it into index delete as the item deleter because the index's item sare counters

# testing plan
demonstate that the program detects false inputs
demonstrate that valid inputs result in a properly formatted text file
- this will show that the index data type itself is accurate