

echo -e "IMPLEMENTATION OF NAIVE BAYES ALGORITHM\n\n"


function ask_data
{
   dialog --inputbox "Enter daily time spent" 10 20 2>user_input.txt
   echo -e "\n" 2>> user_input.txt
   
   echo -e "Age"
   read age
   echo -e $age >>user_input.txt
   echo -e "Income"
   read income
   echo -e $income >> user_input.txt
   echo -e "Internet Usage"
   read internet
   echo -e $internet >> user_input.txt
   
}
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

