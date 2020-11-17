#ifndef INVESTMENT_H
#define INVESTMENT_H

#include <list>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

class investment
{
public:
  investment(); //Investment’s constructors
  ~investment(); //Investment’s destructor
  //Stock’s constructors
  //Stock’s destructor
  void setup_investment();
  void get_trend();
  void rsi(list<float> open_day, list<float> close_day, int day); //
  void rsi_no_info(list<float> open_day, list<float> close_day, int day);//
  void stochastic(); //
  void stochastic_no_info();
  void plot_stochastic();
  void plot_rsi();
  void plot_stock();
  void initiate_suggestion_system();
  double *open;
  double *close;
  double *volume;
  double *change;
  int days;
  string name;
  bool overpriced; //= false; //
  bool hold; //= false;
  bool overbought; //= false; //
  double trend_prediction;
  ofstream histFile;
  void read_csv(string file_name); //
  void calc_change();
  double *rsi_val;
  double *stoch;
  int *suggestions;
  int correct;
  void gen_suggestions(float rsi_entered, float stoch_entered); //
  void gen_suggestions_no_comment(float rsi_entered, float stoch_entered);

  float compare_suggestions(int day);
  float compare_suggestions_no_comment(int day);


  list<float> open_stocks;
  list<float> open_last_14;
  list<float> close_stocks;
  list<float> close_last_14;
  //void check_vector();
  float rs;
  float rsi_value;
  float SO;
};

#endif
