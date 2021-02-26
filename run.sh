
#script to run the algorithm by taking various input by making use of windows 
echo -e "IMPLEMENTATION OF NAIVE BAYES ALGORITHM\n\n"


function ask_data
{
    dialog --backtitle "Dialog Form" --title "user input" \
    --form "\nEnter the details" 25 60 16 \
   "Daily time limit:" 1 1 "Value 1" 1 25 25 30 \
   "Age:" 2 1 "Value 2" 2 25 25 30 \
   "Income:" 3 1 "Value 3" 3 25 25 30 \
   "Internet usage:" 4 1 "Value 4" 4 25 25 30 \
2>user_input.txt   
}
#function which asks the user to enter the input into the window

dialog --yesno "Do you want to enter your own data?" 10 20
if [ $? -eq 0 ]
then 
    g++ naive.cpp -o naive;
    ./naive;
    echo "The entered data is"
    echo "new_data.csv" > user_input.txt
    g++ naive_algo.cpp -o algo
    ask_data;
    ./algo < user_input.txt
else
    echo "The existing data will be used"
    g++ naive_algo.cpp -o algo
    echo "data.csv" > user_input.txt
    ask_data;
    ./algo < user_input.txt
fi
#the above lines of code deal with 2 situations one when the user wants to enter his own data and the other when he makes use of the existing data

