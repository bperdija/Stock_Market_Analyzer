#include "Stock.h"
//#include "gnuplot-cpp/gnuplot_i.hpp"

// Default instructor for the investment class, used for compilation. No precondition.
investment::investment()
{

}

// Default destructor for the investment class, used for deleting the class. No precondition.
investment::~investment()
{

}

// The rsi_no_info() function is used to calculate the rsi, and write to the rs and rsi member variables of the investment class. Precondition: read_csv() must have been called to create lists of stocks for closing and opening day values. Parameters include the open day values, close day values, and the day that will be examined. Postcondition: Writes to the rs and rsi member variables of the investment class. **Unlike the rsi() function, rsi_no_info() will not output any information to the display and will only be used when calculating the rs and rsi of all 58 days.
void investment::rsi_no_info(list<float> open_day, list<float> close_day, int day)
{
  int day_given = day;
  float AvgUp;
  float AvgDown;
  list<float> change;
  list<float> positive;
  list<float> negative;

  list<float>::iterator open = open_day.begin();
  for(int h = 0; h < (day_given - 14); h++, open++)
  {
  }

  list<float>::iterator close = close_day.begin();
  for(int j = 0; j < (day_given - 14); j++, close++)
  {
  }

  for (int hopper = 0; hopper < 14; hopper++, close++, open++)
  {
    float c = *close;
    close_last_14.push_back(c);

    float o = *open;
    open_last_14.push_back(o);
    float difference = (c - o);
    change.push_back(difference);
  }

  list<float>::iterator iter;
  for (iter = change.begin(); iter != change.end(); iter++)
  {
    if (*iter >= 0)
    {
      positive.push_back(*iter);
    }
    else
    {
      negative.push_back(*iter);
    }
  }

  list<float>::iterator iter2;
  for (iter2 = positive.begin(); iter2 != positive.end(); iter2++)
  {
    float temp = *iter2;
    AvgUp = (AvgUp+temp);
  }
  AvgUp = (AvgUp/(positive.size()));

  list<float>::iterator iter3;
  for (iter3 = negative.begin(); iter3 != negative.end(); iter3++)
  {
    float temp = *iter3;
    AvgDown = (AvgDown+temp);
  }
  AvgDown = abs(AvgDown);
  AvgDown = (AvgDown/(negative.size()));
  rs = AvgUp/AvgDown;
  rsi_value = ((100)-((100)/(1+rs)));
}

// The stochastic_no_info() function is used to calculate the stochastic Oscillator, and write to the SO member variables of the investment class. Precondition: read_csv() must have been called to create lists of stocks. There are no parameters, but this function will access member variables in the investment class. Postcondition: Writes to the SO member variables of the investment class. **Unlike the stochastic() function, stochastic_no_info() will not output any information to the display and will only be used when calculating the SO of all 58 days.
void investment::stochastic_no_info()
{
  float highest = 0;
  float lowest = 0;
  float closing_val;

  list<float>::iterator iter5;
  lowest = *close_last_14.begin();
  for (iter5 = close_last_14.begin(); iter5 != close_last_14.end(); ++iter5)
  {
    if (*iter5 > highest)
    {
      highest = *iter5;
    }

    if (*iter5 < lowest)
    {
      lowest = *iter5;
    }
  }

  list<float>::iterator iter6;
  iter6 = close_last_14.end();
  iter6--;
  closing_val = *iter6;
  SO = (((closing_val-lowest)/(highest-lowest))*100);
}

// The gen_suggestions_no_comment() function is used to determine whether a stock is overpriced or overbought depending on the rsi and SO value. Precondition: Takes in rsi_entered and stoch_entered as parameters. These are used to determine whether a stock is overpriced or overbought. Postcondition: Modifies the overpriced, overbought or hold boolians in the investment class. Erases the open_last_14 and close_last_14 lists to deallocate memory.  **Unlike the gen_suggestions() function, gen_suggestions_no_comment() will not output any information to the display and will only be used when outputting a suggestion for all 58 stocks.
void investment::gen_suggestions_no_comment(float rsi_entered, float stoch_entered)
{
  if (rsi_entered >= 70 || stoch_entered >= 70)
  {
    overpriced = true;
  }
  else if (rsi_entered <= 30 || stoch_entered <= 30)
  {
    overbought = true;
  }
  else
  {
    hold = true;
  }

  open_last_14.erase(open_last_14.begin(),open_last_14.end());
  close_last_14.erase(close_last_14.begin(),close_last_14.end());
}

// The compare_suggestions_no_comment() function is used to determine whether it was wise to sell or buy a stock depending on the difference in closing and opening values on the next day. Precondition: takes in the day that the suggestion was originally made for. Postcondition: Returns a 1 if the suggestion made in gen_suggestions_no_comments lead to a beneficial outcome for the user. Returns a 0 if the sugestion harmed the user. Turns overpriced, overbought, and hold booleans false. **Unlike the compare_suggestions() function, compare_suggestions_no_comment() will not output any responses to the display and will only be used when comparing a previously made suggestion to an outcome, for all 58 stocks.
float investment::compare_suggestions_no_comment(int day)
{
  int value = 0;
  list<float>::iterator open = open_stocks.begin();
  for(int h = 0; h < (day+2); h++, open++)
  {
  }

  list<float>::iterator close = close_stocks.begin();
  for(int j = 0; j < (day+2); j++, close++)
  {
  }

  float o = *open;
  float c = *close;
  float difference = (c - o);
  if (difference > 0 && overbought == true)
  {
    value = 1;
  }

  if (difference > 0 && overpriced == true)
  {
    value = 0;
  }

  if (difference < 0 && overbought == true)
  {
    value = 0;
  }

  if (difference < 0 && overpriced == true)
  {
    value = 1;
  }

  if (difference > 0 && hold == true)
  {
    value = 1;
  }

  if (difference < 0 && hold == true)
  {
    value = 0;
  }

  overpriced = false;
  overbought = false;
  hold = false;

  return value;
}

// The rsi() function is used to calculate the rsi, and write to the rs and rsi member variables of the investment class while also outputting information to the user. Precondition: read_csv() must have been called to create lists of stocks for closing and opening day values. Parameters include the open day values, close day values, and the day that will be examined. Postcondition: Writes to the rs and rsi member variables of the investment class while outputting key information (rsi values) to the user.
void investment::rsi(list<float> open_day, list<float> close_day, int day)
{
  int day_given = day;
  while (day_given < 14 || day_given > 58)
  {
    cout << "Cannot calculate rsi before day 14 or after day 58. Pick a new day. " << endl;
    cout << "Day: ";
    cin >> day_given;
  }

  float AvgUp;
  float AvgDown;
  list<float> change;
  list<float> positive;
  list<float> negative;

  list<float>::iterator open = open_day.begin();
  //cout << *open;
  for(int h = 0; h < (day_given - 14); h++, open++)
  {
    //cout << *open << " " << endl;
  }

  list<float>::iterator close = close_day.begin();
  for(int j = 0; j < (day_given - 14); j++, close++)
  {
    //cout << *close << " " << endl;
  }

  //cout << "open and close for the last 14 days" << endl;
  for (int hopper = 0; hopper < 14; hopper++, close++, open++)
  {
    float c = *close;
    //std::cout << "c:"<< c << ' ' << endl;
    close_last_14.push_back(c);

    float o = *open;
    open_last_14.push_back(o);
    //std::cout << "o:"<< o << ' ' << endl;
    float difference = (c - o);
    //cout << difference << " ";
    change.push_back(difference);
  }


  //cout << endl << endl;

  list<float>::iterator iter;
  for (iter = change.begin(); iter != change.end(); iter++)
  {
    if (*iter >= 0)
    {
      positive.push_back(*iter);
    }
    else
    {
      negative.push_back(*iter);
    }
    //std::cout << *iter << ' ';
  }

  //cout << "positive values here: ";
  list<float>::iterator iter2;
  for (iter2 = positive.begin(); iter2 != positive.end(); iter2++)
  {
    float temp = *iter2;
    //cout << *iter2 << " ";
    AvgUp = (AvgUp+temp);
  }
  //cout << endl;
  //cout << "AvgUp before division: " << AvgUp << endl;
  //AvgUp = (AvgUp/(14));
  AvgUp = (AvgUp/(positive.size()));
  //cout <<"AvgUp = "<< AvgUp << endl << endl;

  //cout << endl << endl;

  //cout << "testing negative here: ";
  list<float>::iterator iter3;
  for (iter3 = negative.begin(); iter3 != negative.end(); iter3++)
  {
    float temp = *iter3;
    //cout << *iter3 << " " <<endl;
    AvgDown = (AvgDown+temp);
  }
  //cout << endl;

  AvgDown = abs(AvgDown);

  //AvgDown = (AvgDown/(14));
  AvgDown = (AvgDown/(negative.size()));
  //cout <<"AvgDown = "<< AvgDown << endl << endl;

/*
  for (auto l = open_last_14.begin(); l != open_last_14.end(); ++l)
  {
    std::cout << *l << ' ';
  }
  cout << endl << endl;

  for (auto b = negative.begin(); b != negative.end(); ++b)
  {
    std::cout << *b << ' ';
  }

*/

  cout << endl;


  cout << "Performing RSI Calculation: " << endl;
  cout << "The average of all positive change in the last 14 days is: " << AvgUp << endl;
  cout << "The average of all negative change in the last 14 days is: " << AvgDown << endl;
  rs = AvgUp/AvgDown;
  cout << "RS value: " << rs << endl;
  rsi_value = ((100)-((100)/(1+rs)));
  cout << "The Relative Strength Index (RSI) of the last 14 days is: " << rsi_value << endl;
}

// The stochastic() function is used to calculate the stochastic Oscillator, output information to the user, and write to the SO member variables of the investment class. Precondition: read_csv() must have been called to create lists of stocks. There are no parameters, but this function will access member variables in the investment class. Postcondition: Writes to the SO member variables of the investment class while outputting information (highest value, lowest value and closing value) to the user.
void investment::stochastic() //
{
  float highest = 0;
  float lowest = 0;
  float closing_val;

  cout << "Performing Stochastic Calculation: " << endl;

  list<float>::iterator iter5;
  lowest = *close_last_14.begin();
  for (iter5 = close_last_14.begin(); iter5 != close_last_14.end(); ++iter5)
  {
    if (*iter5 > highest)
    {
      highest = *iter5;
    }

    if (*iter5 < lowest)
    {
      lowest = *iter5;
    }
    //std::cout << "close last 14:"<< *iter5 << ' ' << endl;
  }
  cout << "Lowest closing value in the last 14 days: " << lowest << endl;
  cout << "Highest closing value in the last 14 days: " << highest << endl;


  list<float>::iterator iter6;
  iter6 = close_last_14.end();
  iter6--;
  closing_val = *iter6;
  cout << "closing value: " << closing_val << endl;

  SO = (((closing_val-lowest)/(highest-lowest))*100);
  cout << "Stochastic Oscillator Value: " << SO;

}

// The gen_suggestions() function is used to determine whether a stock is overpriced or overbought depending on the rsi and SO value, and outputs a suggestion to the user. Precondition: Takes in rsi_entered and stoch_entered as parameters. These are used to determine whether a stock is overpriced or overbought. Postcondition: Modifies the overpriced, overbought or hold boolians in the investment class and outputs a suggestion to the user of what to do with their stocks. Erases the open_last_14 and close_last_14 lists to deallocate memory.
void investment::gen_suggestions(float rsi_entered, float stoch_entered)
{
  cout << endl;
  cout<< "According to the relative strength Index: ";
  if (rsi_entered >= 70)
  {
    cout << "The stock is overpriced. You should consider selling. " << endl;
  }
  else if (rsi_entered <= 30)
  {
    cout << "The stock is underpriced. You should consider buying. " << endl;
  }
  else
  {
    cout << "You should consider holding on to your stocks. " << endl;
  }


  cout << "According to the Stochastic Oscillator indicator: ";
  if (stoch_entered >= 70)
  {
    cout << "The stock is overpriced and the stock is likely to decrease the next day. You should consider selling. " << endl;
  }
  else if (stoch_entered <= 30)
  {
    cout << "The stock is underpriced. You should consider buying. " << endl;
  }
  else
  {
    cout << "You should consider holding on to your stocks. " << endl;
  }


  cout << "Taking both into consideration...";
  if (rsi_entered >= 70 || stoch_entered >= 70)
  {
    cout << "You should sell your stocks." << endl;
    overpriced = true;
  }
  else if (rsi_entered <= 30 || stoch_entered <= 30)
  {
    cout << "You should buy stock." << endl;
    overbought = true;
  }
  else
  {
    cout << "You should consider holding on to your stocks. " << endl;
    hold = true;
  }

  open_last_14.erase(open_last_14.begin(),open_last_14.end());
  close_last_14.erase(close_last_14.begin(),close_last_14.end());

}

// The compare_suggestions() function is used to determine whether it was wise to sell or buy a stock depending on the difference in closing and opening values on the next day, and let the user know. Precondition: takes in the day that the suggestion was originally made for. Postcondition: Returns a 1 if the suggestion made in gen_suggestions_no_comments lead to a beneficial outcome for the user. Returns a 0 if the sugestion harmed the user. Turns overpriced, overbought, and hold booleans false.
float investment::compare_suggestions(int day)
{
  int value = 0;

  if(overpriced == true)
  {
    cout << "So I mentioned that the stocks were overpriced and that at the end of day " << day << ", you should sell them. ";
  }

  else if(overbought == true)
  {
    cout << "So I mentioned that the stocks were overbought and that at the end of day " << day << ", you should buy them. ";
  }

  else if(hold == true)
  {
    cout << "So I mentioned that at the end of day " << day << ", you should hold onto your stocks. ";
  }

  list<float>::iterator open = open_stocks.begin();
  //cout << *open;
  for(int h = 0; h < (day+2); h++, open++)
  {
    //cout << *open << " " << endl;
  }

  list<float>::iterator close = close_stocks.begin();
  for(int j = 0; j < (day+2); j++, close++)
  {
    //cout << *close << " " << endl;
  }
  float o = *open;
  float c = *close;
  float difference = (c - o);
  cout << "On the following day, the stocks went: " << difference << endl;

  if (difference > 0 && overbought == true)
  {
    cout << "NICE! Stocks went up so you've made money! I was right!" << endl;
    value = 1;
  }

  if (difference > 0 && overpriced == true)
  {
    cout << "Hmm... I ugh, don't know how to break this to you chief but stocks went up a day later so you would've made money buying stocks... I was wrong." << endl;
    value = 0;
  }

  if (difference < 0 && overbought == true)
  {
    cout << "Umm... So stocks went down a day later which means you've lost some money. Hey, I wouldn't trust a program coded by a 20 year old why should you? I was wrong okay!!?" << endl;
    value = 0;
  }

  if (difference < 0 && overpriced == true)
  {
    cout << "I don't want to brag or anything but stocks went down a day later and I just saved you some money telling you to sell them early. Go me." << endl;
    value = 1;
  }

  if (difference > 0 && hold == true)
  {
    cout << "Well stocks went up the following day, but at least i didn't tell you to sell them yesterday. So I guess I predicted correctly." << endl;
    value = 1;
  }

  if (difference < 0 && hold == true)
  {
    cout << "Well stocks went down the following day, so I probably should have told you to sell them. At least I didn't tell you to buy stocks! I guess i predicted incorrectly since you lost money." << endl;
    value = 0;
  }

  overpriced = false;
  overbought = false;
  hold = false;

  return value;
}

// The read_csv() function is used to read a csv file and write to the open and close lists in the investment class. Precondition: the file_name that is looked at is used as a parameter Postcondition: writes to the open and close list members in the investment class.
void investment::read_csv(string file_name)
{

  // variables
  string temp_open;
  string temp_close;

  // define 4 empty arrays to store values
  std::list<float> open;
  std::list<float> close;

  string file = file_name;

  int i = 0;

  ifstream myFile;
  myFile.open(file);
  if(myFile.is_open()) // while the file is open
  {
    while(!myFile.eof())
    {
      getline(myFile, temp_open, ',');
      //cout << temp_open;
      float temp = strtof((temp_open).c_str(), 0); // string to float with help from https://www.cplusplus.com/forum/beginner/148948/

      //cout << temp << endl;
      open.push_back(temp);


      getline(myFile,temp_close, '\n');
      float temp2 = strtof((temp_close).c_str(),0);
      close.push_back(temp2);
    }
  }
  open_stocks = open;
  close_stocks = close;


  /*
  for (auto i = open.begin(); i != open.end(); ++i)
  {
    std::cout << *i << ' ';
  }
  cout << "done" << endl;
  */

}

// Default instructor for the Stock class, used for compilation. No precondition.
Stock::Stock()
{

}
// Default destructor for the Stock class, used for compilation. No precondition.
Stock::~Stock()
{

}


int main()
{
  Stock AMD;
  Stock Nividia;
  Stock Tesla;

  list<investment *> inv_list;
  inv_list.push_back(&Tesla);
  inv_list.push_back(&Nividia);
  inv_list.push_back(&AMD);

  AMD.read_csv("amd.csv");
  Nividia.read_csv("nvda.csv");
  Tesla.read_csv("tesla.csv");
  //AMD.check_vector();
  //list<investment> listOfItems;
  //listOfItems.push_back(Nividia);

  bool menu = true;
  float suggestions = 0;
  float correct_suggestions = 0;
  while (menu == true)
  {
    cout << "What company would you like to look at? Type 'a' for AMD, 'n' for Nividia, and 't' for Tesla. Type in 'x' to exit. " << endl << "Choice: ";
    string given;
    getline(cin, given);
    // Create a new character type variable named "response", and have it equal only the first letter of the string "given".
    char choice = given[0];
    if (choice == 'a' || choice == 'A')
    {
      cout << "Would you like to look at all 58 days or just one? Select 'a' for all, and 'b' for one. " << endl << "Choice: ";
      string response;
      getline(cin, response);
      char choice2 = response[0];
      if (choice2 == 'a')
      {
        cout << endl;
        float temp_suggestions = 0;
        float temp_correct_suggestions = 0;

        for (int day = 14; day < 57; day++)
        {
          AMD.rsi_no_info(AMD.open_stocks, AMD.close_stocks, day);
          AMD.stochastic_no_info();
          AMD.gen_suggestions_no_comment(AMD.rsi_value, AMD.SO);
          temp_suggestions++;
          temp_correct_suggestions = temp_correct_suggestions + AMD.compare_suggestions_no_comment(day);
        }

        cout << "Suggestions provided: " << temp_suggestions << endl;
        cout << "Number of correct suggestions: " << temp_correct_suggestions << endl;
        cout << "This predictor is: %" << ((temp_correct_suggestions/temp_suggestions)*100) << " accurate." << endl << endl;
      }

      else if (choice2 == 'b')
      {
        int day;
        cout << endl << "Which day would you like to look at? Please note, day 0 is the first day, and day 58 is the last day. Your range of choices is day 14 to 58. " << endl << "Choice: ";
        cin >> day;
        while(day < 14 || day > 58)
        {
          cout << "Cannot calculate rsi before day 14 or after day 58. Pick a new day. " << endl;
          cout << "Day: ";
          cin >> day;
        }
        cin.ignore();
        AMD.rsi(AMD.open_stocks, AMD.close_stocks, day);
        cout << endl;
        AMD.stochastic();
        cout << endl;
        AMD.gen_suggestions(AMD.rsi_value, AMD.SO);
        cout << endl;
        if (day == 58)
        {
          cout << "Since this is the last day on the list, we don't know how are prediction will hold up. Good luck! ";
        }
        else
        {
          suggestions++;
          cout << "Let's let the day pass and see if my prediction was a good one." << endl;
          correct_suggestions = correct_suggestions + AMD.compare_suggestions(day);
        }

        cout << endl;
        cout << "Suggestions provided: " << suggestions << endl;
        cout << "Number of correct suggestions: " << correct_suggestions << endl;
        cout << "This predictor is: %" << ((correct_suggestions/suggestions)*100) << " accurate." << endl << endl;
      }

      else
      {
        cout << "Unknown entry. Going back to the menu. " << endl;
      }

      //cin.ignore();
    }

    else if (choice == 'n' || choice == 'N')
    {
      cout << "Would you like to look at all 58 days or just one? Select 'a' for all, and 'b' for one. " << endl << "Choice: ";
      string response;
      getline(cin, response);
      char choice2 = response[0];
      if (choice2 == 'a')
      {
        cout << endl;
        float temp_suggestions = 0;
        float temp_correct_suggestions = 0;

        for (int day = 14; day < 57; day++)
        {
          Nividia.rsi_no_info(Nividia.open_stocks, Nividia.close_stocks, day);
          Nividia.stochastic_no_info();
          Nividia.gen_suggestions_no_comment(Nividia.rsi_value, Nividia.SO);
          temp_suggestions++;
          temp_correct_suggestions = temp_correct_suggestions + Nividia.compare_suggestions_no_comment(day);
        }

        cout << "Suggestions provided: " << temp_suggestions << endl;
        cout << "Number of correct suggestions: " << temp_correct_suggestions << endl;
        cout << "This predictor is: %" << ((temp_correct_suggestions/temp_suggestions)*100) << " accurate." << endl << endl;
      }

      else if (choice2 == 'b')
      {
        int day;
        cout << endl << "Which day would you like to look at? Please note, day 0 is the first day, and day 58 is the last day. Your range of choices is day 14 to 58. " << endl << "Choice: ";
        cin >> day;
        while(day < 14 || day > 58)
        {
          cout << "Cannot calculate rsi before day 14 or after day 58. Pick a new day. " << endl;
          cout << "Day: ";
          cin >> day;
        }
        cin.ignore();
        Nividia.rsi(Nividia.open_stocks, Nividia.close_stocks, day);
        cout << endl;
        Nividia.stochastic();
        cout << endl;
        Nividia.gen_suggestions(Nividia.rsi_value, Nividia.SO);
        cout << endl;
        if (day == 58)
        {
          cout << "Since this is the last day on the list, we don't know how are prediction will hold up. Good luck! ";
        }
        else
        {
          suggestions++;
          cout << "Let's let the day pass and see if my prediction was a good one." << endl;
          correct_suggestions = correct_suggestions + Nividia.compare_suggestions(day);
        }

        cout << endl;
        cout << "Suggestions provided: " << suggestions << endl;
        cout << "Number of correct suggestions: " << correct_suggestions << endl;
        cout << "This predictor is: %" << ((correct_suggestions/suggestions)*100) << " accurate." << endl << endl;
      }

      else
      {
        cout << "Unknown entry. Going back to the menu. " << endl;
      }

      //cin.ignore();
    }

    else if (choice == 't' || choice == 'T')
    {
      cout << "Would you like to look at all 58 days or just one? Select 'a' for all, and 'b' for one. " << endl << "Choice: ";
      string response;
      getline(cin, response);
      char choice2 = response[0];
      if (choice2 == 'a')
      {
        cout << endl;
        float temp_suggestions = 0;
        float temp_correct_suggestions = 0;

        for (int day = 14; day < 57; day++)
        {
          Tesla.rsi_no_info(Tesla.open_stocks, Tesla.close_stocks, day);
          Tesla.stochastic_no_info();
          Tesla.gen_suggestions_no_comment(Tesla.rsi_value, Tesla.SO);
          temp_suggestions++;
          temp_correct_suggestions = temp_correct_suggestions + Tesla.compare_suggestions_no_comment(day);
        }

        cout << "Suggestions provided: " << temp_suggestions << endl;
        cout << "Number of correct suggestions: " << temp_correct_suggestions << endl;
        cout << "This predictor is: %" << ((temp_correct_suggestions/temp_suggestions)*100) << " accurate." << endl << endl;
      }

      else if (choice2 == 'b')
      {
        int day;
        cout << endl << "Which day would you like to look at? Please note, day 0 is the first day, and day 58 is the last day. Your range of choices is day 14 to 58. " << endl << "Choice: ";
        cin >> day;
        while(day < 14 || day > 58)
        {
          cout << "Cannot calculate rsi before day 14 or after day 58. Pick a new day. " << endl;
          cout << "Day: ";
          cin >> day;
        }
        cin.ignore();
        Tesla.rsi(Tesla.open_stocks, Tesla.close_stocks, day);
        cout << endl;
        Tesla.stochastic();
        cout << endl;
        Tesla.gen_suggestions(Tesla.rsi_value, Tesla.SO);
        cout << endl;
        if (day == 58)
        {
          cout << "Since this is the last day on the list, we don't know how are prediction will hold up. Good luck! ";
        }
        else
        {
          suggestions++;
          cout << "Let's let the day pass and see if my prediction was a good one." << endl;
          correct_suggestions = correct_suggestions + Tesla.compare_suggestions(day);
        }

        cout << endl;
        cout << "Suggestions provided: " << suggestions << endl;
        cout << "Number of correct suggestions: " << correct_suggestions << endl;
        cout << "This predictor is: %" << ((correct_suggestions/suggestions)*100) << " accurate." << endl << endl;
      }

      else
      {
        cout << "Unknown entry. Going back to the menu. " << endl;
      }

      //cin.ignore();
    }

    else if (choice == 'x' || choice == 'X')
    {
      menu = false;
    }

    else
    {
      cout << "Input not recognized. Please input an appropriate response. " << endl;
    }
  }

  cout << endl << "Good bye" << endl;

  return 0;
}
