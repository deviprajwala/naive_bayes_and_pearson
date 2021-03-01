
#script to run the algorithm by taking various input by making use of windows 
#echo -e "IMPLEMENTATION OF NAIVE BAYES ALGORITHM\n\n"

function ask_data
#function which asks the user to enter the input into the window
{
    dialog --backtitle "Dialog Form" --title "user input" \
    --form "\nEnter the details" 25 60 16 \
   "Daily time limit:" 1 1 "Value 1" 1 25 25 30 \
   "Age:" 2 1 "Value 2" 2 25 25 30 \
   "Income:" 3 1 "Value 3" 3 25 25 30 \
   "Internet usage:" 4 1 "Value 4" 4 25 25 30 \
2>user_input.txt   
}


dialog --yesno "Do you want to enter your own data?" 10 20
#user is given the chance to enter his own data or make use of the existing data
if [ $? -eq 0 ]
then 
    g++ naive_data.cpp -o naive
    #naive.cpp is compiled

    ./naive
    #program is executed

    #echo "The entered data is"
    echo "data.csv" > user_input.txt
    #string is written to text file

    g++ naive_algo.cpp -o algo
    #program is compiled

else
    echo "The existing data will be used"
    
    echo "advertising.csv" > user_input.txt
    #string is written to text file

    g++ naive_algo.cpp -o algo
    #program is compiled

   
fi
ask_data;
#function is called to enter data

./algo < user_input.txt > output.sh
#program is executed

./output.sh
#script is executed

#the above lines of code deal with 2 situations one when the user wants to enter his own data and the other when he makes use of the existing data


dialog --yesno "Do you want to check for the recommendation of places?" 10 20
#user is asked if wants the recommendation or not
if [ $? -eq 0 ]
then
    #script to run the pearson algorithm
    # echo -e "Pearson's prediction\n\n"


    function ask_data_pearson {
    #function which asks the user to enter the input into the window

    dialog --backtitle "Dialog Form" --title "user input" \
    --form "\nEnter the ratings" 25 60 16 \
   "Church:" 2 1 "Value 2" 2 25 25 30 \
   "Resort:" 3 1 "Value 3" 3 25 25 30 \
   "Beach:" 4 1 "Value 4" 4 25 25 30 \
   "Park:" 5 1 "Value 5" 5 25 25 30 \
   "Theatre:" 6 1 "Value 6" 6 25 25 30 \
   "Meuseum:" 7 1 "Value 7" 7 25 25 30 \
   "Mall:" 8 1 "Value 8" 8 25 25 30 \
   "Zoo:" 9 1 "Value 9" 9 25 25 30 \
   2>pearson_input.txt   
   }


   dialog --yesno "Do you want to enter your own data?" 10 20
   #user is given the chance to enter his own data or make use of the existing data
   if [ $? -eq 0 ]
   then 
     g++ pearson_data.cpp -o pearson_data
     #program is compiled

     ./pearson_data 
     #program is executed
    echo "Enter number of users"
    read n
    echo $n > pearson_input.txt
    echo "10\n" > pearson_input.txt

     g++ pearson_algo.cpp -o pearson
     #program is compiled
     
   else
    echo "The existing data will be used"

    echo "google_review_ratings.csv\n" > pearson_input.txt
    echo "5456\n" >> pearson_input.txt
    echo "10\n" > pearson_input.txt
    #string is written to text file
    
    g++ pearson_algo.cpp -o pearson
    #program is compiled

    fi
    ask_data_pearson;
    #function is called to enter data

    ./pearson < pearson_input.txt > output.sh
    #program is executed

    ./output.sh
    #script is executed
fi
clear