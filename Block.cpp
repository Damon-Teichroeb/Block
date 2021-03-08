//**********************************************************************
//* Author:   Damon L. Teichroeb                                       *
//* Language: C++                                                      *
//* Format:   Windows Command Prompt                                   *
//* ------------------------------------------------------------------ *
//*                 This is what the program creates:                  *
//* ------------------------------------------------------------------ *
//* 4 length, 4 width, 3 depth    |  |    6 length, 5 width, 0 depth   *
//* Volume: 48                    |  |    Area: 30                     *
//*          __________           |  |           ___________           *
//*         /         /|          |  |          |           |          *
//*        /_________/ |          |or|          |           |          *
//*        |         | |          |  |          |           |          *
//*        |         | |          |  |          |           |          *
//*        |         | /          |  |          |           |          *
//*        |_________|/           |  |          |___________|          *
//*                               |  |                                 *
//**********************************************************************

#include <cmath>
#include <iostream>
using namespace std;

//**********************************************************************
//*                         Symbolic Constants                         *
//**********************************************************************
#define SPACE        ' '
#define WIDTH_BAR    '_'
#define LENGTH_BAR   '|'
#define DEPTH_BAR    '/'
#define WIDTH_FACTOR 2.25f
#define DEPTH_FACTOR 0.75f

//**********************************************************************
//*                          Program Classes                           *
//**********************************************************************
// The specifications of a block
class block
{
   int depth,
       length,
       width;
public:
        block     (int l,      int w,     int d) 
                  {length = l, width = w, depth = d;}

   void draw_block();
   void no_depth  (int &new_width);
};

//**********************************************************************
//*                        Draw a block picture                        *
//**********************************************************************
void block::draw_block()
{
   int fast_counter,
       new_depth,
       new_width,
       slow_counter;

   new_width = (int)round(width * WIDTH_FACTOR);

   if (depth == 0)
      no_depth(new_width);
   else
   {
      cout << "\n\nThis block is "           << length
           <<     " length by "              << width
           <<     " width by "               << depth
           <<     " depth with a volume of " << length * width * depth
           << ":";
		   
	  new_depth = (int)round(depth * DEPTH_FACTOR);

      cout << "\n";
      for (fast_counter = 1; fast_counter <= new_depth; fast_counter++)
         cout << SPACE;

      // This loop adds one more width bar to the series on the very top:
      //                                    |new_width + 1|
      for (fast_counter = 1; fast_counter <= new_width + 1; fast_counter++)
         cout << WIDTH_BAR;

      // This loop creates the entire top portion of the block
      // just before the next series of width bars
      for (slow_counter = 1; slow_counter < new_depth; slow_counter++)
      {
         cout << "\n";
         for (fast_counter = slow_counter; fast_counter < new_depth; fast_counter++)
            cout << SPACE;
         cout << DEPTH_BAR;
         for (fast_counter = 1; fast_counter <= new_width; fast_counter++)
            cout << SPACE;
         cout << DEPTH_BAR;

         if (slow_counter <= length)
         {
            for (fast_counter = 1; fast_counter < slow_counter; fast_counter++)
               cout << SPACE;
            cout << LENGTH_BAR;
         }
         else
         {
            for (fast_counter = 1; fast_counter <= length; fast_counter++)
               cout << SPACE;
            cout << DEPTH_BAR;
         }
      }

      // These loops create the middle series of bars
      cout << "\n" << DEPTH_BAR;
      for (fast_counter = 1; fast_counter <= new_width; fast_counter++)
         cout << WIDTH_BAR;
      cout << DEPTH_BAR;

      if (new_depth > length)
      {
         for (fast_counter = 1; fast_counter <= length; fast_counter++)
            cout << SPACE;
         cout << DEPTH_BAR;
      }
      else
      {
         for (fast_counter = 1; fast_counter < slow_counter; fast_counter++)
            cout << SPACE;
         cout << LENGTH_BAR;
      }

      // This loop creates the entire bottom portion of the block
      // just after the middle series of width bars
      for (slow_counter = 1; slow_counter <= length; slow_counter++)
      {
         cout << "\n" << LENGTH_BAR;
         for (fast_counter = 1; fast_counter <= new_width; fast_counter++)
            if (slow_counter == length)
               cout << WIDTH_BAR;
            else
               cout << SPACE;
         cout << LENGTH_BAR;

         if (slow_counter <= (length - new_depth))
         {
            for (fast_counter = 1; fast_counter < new_depth; fast_counter++)
               cout << SPACE;
            cout << LENGTH_BAR;
         }
         else
         {
            for (fast_counter = slow_counter; fast_counter < length; fast_counter++)
               cout << SPACE;
            cout << DEPTH_BAR;
         }
      }
   }
   return;
}

//**********************************************************************
//*                 Draw a block picture with no depth                 *
//**********************************************************************
void block::no_depth(int &new_width)
{
   int fast_counter,
       slow_counter;

   cout << "\n\nThis flat block is "     << length
        <<     " length by "             << width
        <<     " width by "              << depth
        <<     " depth with an area of " << length * width << ":";

   cout << "\n" << SPACE;
   for (fast_counter = 1; fast_counter <= new_width; fast_counter++)
     cout << WIDTH_BAR;

   for (slow_counter = 1; slow_counter <= length; slow_counter++)
   {
      cout << "\n" << LENGTH_BAR;
      for (fast_counter = 1; fast_counter <= new_width; fast_counter++)
         if (slow_counter == length)
            cout << WIDTH_BAR;
         else
            cout << SPACE;
      cout << LENGTH_BAR;
   }
   return;
}

//**********************************************************************
//*                        Function Prototypes                         *
//**********************************************************************
void introduction();
void get_block_dimensions(int *p_length, int *p_width, int *p_depth);

//**********************************************************************
//*                           Main Function                            *
//**********************************************************************
int main()
{
   char answer;
   int  user_depth,
        user_length,
        user_width;

   introduction();

   block example_block1(1, 1, 1),
         example_block2(5, 5, 2),
         example_block3(3, 4, 0);

   cout << "\n\nHere are some example blocks.";
   example_block1.draw_block();
   example_block2.draw_block();
   example_block3.draw_block();

   // Repeatable user block creation
   do
   {
      get_block_dimensions(&user_length, &user_width, &user_depth);

      block user_block(user_length, user_width, user_depth);

      user_block.draw_block();

      cout << "\n\nDo you want to make another block (Y/N)?: ";
      cin  >> answer;
      answer = toupper(answer);
   }
   while (answer == 'Y');

   cout << "\nThanks for creating blocks! ;-)\n\n";
   return 0;
}

//**********************************************************************
//*                       Print the introduction                       *
//**********************************************************************
void introduction()
{
   cout << "\n\nWelcome to my program!"
        <<   "\nThis program asks for dimensions and creates a block picture."
        <<   "\n-------------------------------------------------------------";
   return;
}

//**********************************************************************
//*                      Get the block dimensions                      *
//**********************************************************************
void get_block_dimensions(int *p_length, int *p_width, int *p_depth)
{
   cout << "\n\nPlease input the length of your block: ";
   cin  >> *p_length;
   while (*p_length <= 0)
   {
      cout << "Sorry, please input a length that is greater than 0: ";
      cin  >> *p_length;
   }

   cout << "Please input the width  of your block: ";
   cin  >> *p_width;
   while (*p_width <= 0)
   {
      cout << "Sorry, please input a width that is greater than 0: ";
      cin  >> *p_width;
   }

   cout << "Please input the depth  of your block: ";
   cin  >> *p_depth;
   while (*p_depth < 0)
   {
      cout << "Sorry, please input a depth that is greater than or equal to 0: ";
      cin  >> *p_depth;
   }
   return;
}