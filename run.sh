

echo -e "IMPLEMENTATION OF NAIVE BAYES ALGORITHM\n\n"

function enter_manually
{
  g++ naive.cpp -o naive;
  ./naive;
  echo "The entered data is"
  cat  data.csv
}

function use_existing
{
  echo "The existing data will be used"
}

function menu
{
  echo -e "\t Enter option regarding the choice of data\n"
  echo -e "\t 1 to Enter data manually\n"
  echo -e "\t 2 to Use existing data\n"

  read -n 1 option
}
 
menu
 
case $option in
0) break;;
1) enter_manually;;
2) use_existing;;
*) clear
   echo "wrong selection";;
esac
