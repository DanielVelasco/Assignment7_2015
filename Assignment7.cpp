#include <iostream>
#include <fstream>
#include <string>
//#include <sstream>
#include <cstring>
#include <cstdlib>
#include <json/json.h>
#include <stdio.h>
#include "MovieTree.h"
using namespace std;

int main(int argc, char* argv[])
{

MovieTree* MovieTreeInit = new MovieTree();

MovieTreeInit->InitOutputJsonObject();


string str;


std::ifstream in(argv[1]);
std::string text;


           string temp[4];
           string tempWord ="";
            int counter = 0;
            while (std::getline(in, text))
                {


                    for(int i=0;i<text.length();i++)
                    {

                        const char* strdata = text.c_str();

                        if(strdata[i]!=44)
                        {
                            tempWord += text[i];




                        }else
                        {


                           temp[counter] = tempWord;
                           tempWord ="";
                            counter++;


                        }  if(i == text.length()-1){


                            temp[3] = tempWord;
                            counter = 0;
                              tempWord ="";

                        }

                    }

                counter = 0;
                tempWord = "";


               string title = temp[1];
               int year =  atoi(temp[2].c_str() );
               int rating =  atoi(temp[0].c_str());
               int quantity = atoi(temp[3].c_str());



               MovieNode *tempNode = new MovieNode(rating,title,year,quantity);

               MovieTreeInit->rbAddFixup(tempNode);


                temp[0].clear();
                temp[1].clear();
                temp[2].clear();
                temp[3].clear();



                }




    int choice = 0;
    do
    {
        cout
             << "======Main Menu=====" << endl
             << "1. Rent a movie" << endl
             << "2. Print the inventory" << endl
             << "3. Delete a movie" << endl
             << "4. Count the movies" << endl
             << "5. Count the longest path" << endl
             << "6. Quit" << endl;

        cin >> choice;

      if(choice == 1)
      {


            cin.ignore();

            string mystr;
            cout << "Enter title:" << endl;
            getline (cin, mystr);

            MovieTreeInit->MovieFound = 0;



            MovieTreeInit->searchMovieTree(MovieTreeInit->root,mystr,MovieTreeInit->Assignment6Output);

            if(MovieTreeInit->MovieFound == 0)
            {
                MovieTreeInit->MovieSearchFound = MovieTreeInit->root;
                MovieTreeInit->MovieSearchFound->quantity = 0;
                cout << "Movie not found" << endl;

            }


             MovieTreeInit->AddToJson("rent",mystr, MovieTreeInit->MovieSearchFound);

            if(MovieTreeInit->MovieSearchFound->quantity ==0)
            {
                MovieTreeInit->AddToJson("delete",mystr, MovieTreeInit->MovieSearchFound);

            }





        }if(choice == 2)
        {


            MovieTreeInit->jArray = json_object_new_array();

            MovieTreeInit->printMovieInventory(MovieTreeInit->root, MovieTreeInit->Assignment6Output);

            MovieTreeInit->AddToJson("traverse","none specified",MovieTreeInit->root);


        }if(choice == 3)
        {



            cin.ignore();

            string mystr;
            cout << "Enter title:" << endl;
            getline (cin, mystr);

            MovieTreeInit->jArray = json_object_new_array();
            MovieTreeInit->MovieFound = 0;
            MovieTreeInit->IsMovieInTree(mystr,MovieTreeInit->root);

            cout << MovieTreeInit->MovieFound << endl;

           if(MovieTreeInit->MovieFound == 1)
            {

                MovieTreeInit->deleteMovieNode(mystr);


            }



               MovieTreeInit->AddToJson("delete",mystr,MovieTreeInit->root);


        }if(choice == 4)
        {


            MovieTreeInit->MovieCount = 1;
            MovieTreeInit->countMovieNodes(MovieTreeInit->root);
            cout << "There are " << MovieTreeInit->MovieCount << " movies in the tree." << endl;
            MovieTreeInit->AddToJson("count","no parameter specified",MovieTreeInit->root);

        }if(choice == 5)
        {

            MovieTreeInit->HeightTree = MovieTreeInit->countLongestPath(MovieTreeInit->root);
            MovieTreeInit->AddToJson("height","no parameter specified",MovieTreeInit->root);

        }if(choice == 6)
        {


            cout << "Goodbye!" << endl;
            cout<<json_object_to_json_string_ext(MovieTreeInit->Assignment6Output, JSON_C_TO_STRING_PRETTY)<<endl;
            ofstream myfile;
            myfile.open ("Assignment7Output.txt");
            myfile << json_object_to_json_string_ext(MovieTreeInit->Assignment6Output, JSON_C_TO_STRING_PRETTY);
            myfile.close();
            break;




        }


}while(choice != 6);



    return 0;
}
