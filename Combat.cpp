#include "glue.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <ncurses.h>
#include <unistd.h>

using namespace std;
Item taco = Item("Taco",1,1,0);

//There are 17 maps in total
Monster Monster_Table[17][5] = {{Monster("slime",5,1,1,5,100,1,taco),Monster("slime2",5,1,1,5,100,1,taco),Monster("slime3",5,1,1,5,100,1,taco),Monster("slime4",5,1,1,5,100,1,taco),Monster("expslime",5,1,1,100,100,1,taco)}, //Dessert Village
{Monster("Cabbage Slime",5,1,1,50,100,1,taco),Monster("Slime's Brother",5,1,1,50,100,1,taco),Monster("It's a slime",5,1,1,50,100,1,taco),Monster("OHNO SLIME",5,1,1,50,100,1,taco),Monster("OHNO bug",5,1,1,50,100,1,taco)}, //Dessert Desert
{Monster("slime",5,1,1,50,100,1,taco),Monster("slime2",5,1,1,50,100,1,taco),Monster("slime3",5,1,1,50,100,1,taco),Monster("slime4",5,1,1,50,100,1,taco),Monster("slime5",5,1,1,50,100,1,taco)}, //Dessert Dessert Dungeon
{Monster("slime",5,1,1,50,100,1,taco),Monster("slime2",5,1,1,50,100,1,taco),Monster("slime3",5,1,1,50,100,1,taco),Monster("slime4",5,1,1,50,100,1,taco),Monster("slime5",5,1,1,50,100,1,taco)}, //Cabbage Campo1
{Monster("slime",5,1,1,50,100,1,taco),Monster("slime2",5,1,1,50,100,1,taco),Monster("slime3",5,1,1,50,100,1,taco),Monster("slime4",5,1,1,50,100,1,taco),Monster("slime5",5,1,1,50,100,1,taco)}, //Cabbage Campo Dungeon
{Monster("slime",5,1,1,50,100,1,taco),Monster("slime2",5,1,1,50,100,1,taco),Monster("slime3",5,1,1,50,100,1,taco),Monster("slime4",5,1,1,50,100,1,taco),Monster("slime5",5,1,1,50,100,1,taco)}, //Cabbage Campo2
{Monster("slime",5,1,1,50,100,1,taco),Monster("slime2",5,1,1,50,100,1,taco),Monster("slime3",5,1,1,50,100,1,taco),Monster("slime4",5,1,1,50,100,1,taco),Monster("slime5",5,1,1,50,100,1,taco)}, //Cabbage Campo2 Dungeon
{Monster("slime",5,1,1,50,100,1,taco),Monster("slime2",5,1,1,50,100,1,taco),Monster("slime3",5,1,1,50,100,1,taco),Monster("slime4",5,1,1,50,100,1,taco),Monster("slime5",5,1,1,50,100,1,taco)}, //Carrot Canyon1
{Monster("slime",5,1,1,50,100,1,taco),Monster("slime2",5,1,1,50,100,1,taco),Monster("slime3",5,1,1,50,100,1,taco),Monster("slime4",5,1,1,50,100,1,taco),Monster("slime5",5,1,1,50,100,1,taco)}, //Carrot Canyon1 Dungeon
{Monster("slime",5,1,1,50,100,1,taco),Monster("slime2",5,1,1,50,100,1,taco),Monster("slime3",5,1,1,50,100,1,taco),Monster("slime4",5,1,1,50,100,1,taco),Monster("slime5",5,1,1,50,100,1,taco)}, //Carrot Canyon2
{Monster("slime",5,1,1,50,100,1,taco),Monster("slime2",5,1,1,50,100,1,taco),Monster("slime3",5,1,1,50,100,1,taco),Monster("slime4",5,1,1,50,100,1,taco),Monster("slime5",5,1,1,50,100,1,taco)}, //Carrot Canyon2 Dungeon
{Monster("slime",5,1,1,50,100,1,taco),Monster("slime2",5,1,1,50,100,1,taco),Monster("slime3",5,1,1,50,100,1,taco),Monster("slime4",5,1,1,50,100,1,taco),Monster("slime5",5,1,1,50,100,1,taco)}, //Soup Sea1
{Monster("slime",5,1,1,50,100,1,taco),Monster("slime2",5,1,1,50,100,1,taco),Monster("slime3",5,1,1,50,100,1,taco),Monster("slime4",5,1,1,50,100,1,taco),Monster("slime5",5,1,1,50,100,1,taco)}, //Soup Sea1 Dungeon
{Monster("slime",5,1,1,50,100,1,taco),Monster("slime2",5,1,1,50,100,1,taco),Monster("slime3",5,1,1,50,100,1,taco),Monster("slime4",5,1,1,50,100,1,taco),Monster("slime5",5,1,1,50,100,1,taco)}, //Soup Sea2 Dungeon
{Monster("slime",5,1,1,50,100,1,taco),Monster("slime2",5,1,1,50,100,1,taco),Monster("slime3",5,1,1,50,100,1,taco),Monster("slime4",5,1,1,50,100,1,taco),Monster("slime5",5,1,1,50,100,1,taco)}}; //Soup Sea3 Dungeon
Monster Rare_Monster_Table[17] = {Monster("Tree Sentinel",100,40,20,1000,1000,0,taco)};
Monster Boss_Monster_Table[17];

//Level Skills table, index = level acquired
Skill Levelup_Skills[10] = {Skill(),Skill(),Skill("Throw Rock","picks up a small rock and hurls it, it's apparently very effective.",2,10,magic_attack),
Skill(),Skill("Dia","using their inner calories, heals their wounds a bit",3,15,healing),Skill(),Skill(),Skill(),Skill(),Skill()};

//Usable on overworld to call up a monster to pass to the combat screen, use the enums to specify "table" in call!
Monster Parse_Monster_Tables(Hero player,int table){
    srand(time(NULL));
    Monster output;
    int choice = 0;
    int location = player.Get_Current_Map();
    switch(table){
        case normal_enemy:
            choice = rand()% 5;
            output = Monster_Table[location][choice];
            break;
        case rare_enemy:
            output = Rare_Monster_Table[location];
            break;
        case boss:
            output = Boss_Monster_Table[location];             
            break;
    }
    return output;
}

int loginc = 0;
string logarray[13];

void DisplayToLog(string output, WINDOW * logwin)
{
    // display output to log window
    logarray[loginc] = output;

    mvwaddstr(logwin, 1+loginc, 1, logarray[loginc].c_str());
    wrefresh(logwin);
    
    loginc++;

    if (loginc >= 12)
    {
        loginc = 12;

        for (int i = 0; i < 13; i++)
        {
            mvwaddstr(logwin, 1+i, 1, "                                                   ");
        }

        for (int i = 0; i < 13; i++)
        {
            logarray[i] = logarray[i+1];
            mvwaddstr(logwin, 1+i, 1, logarray[i].c_str());
        }
        wrefresh(logwin);
    }
}

void DisplayToBattle(string output, WINDOW * battlewin)
{
    // display output to battle window
    logarray[loginc] = output;
    //int inc = 0;
    //string batarray[40];

    mvwaddstr(battlewin, 1+loginc, 1, logarray[loginc].c_str());
    wrefresh(battlewin);
    
    loginc++;

    if (loginc >= 13)
    {
        loginc = 12;

        for (int i = 0; i < 13; i++)
        {
            mvwaddstr(battlewin, 1+i, 1, "                                                   ");
        }

        for (int i = 0; i < 13; i++)
        {
            logarray[i] = logarray[i+1];
            mvwaddstr(battlewin, 1+i, 1, logarray[i].c_str());
        }
        wrefresh(battlewin);
    }
}

void DisplayToControls(string output[10], WINDOW * controlswin)
{

    mvwaddstr(controlswin, 1, 1, "Choose a move:");
    
    for (int i = 0; i < 10; i++)
    {
        mvwaddstr(controlswin, 2+i, 1, output[i].c_str());
    }
    
    wrefresh(controlswin);
    
}
//checks for and applies levelup
void Level_Up(Hero & player,WINDOW * logwin){
    //Level Up formula: floor(base_exp*(level^difficulty_ramp)).  Base_exp = first level up value, difficulty_ramp = how fast exp to next climbs
    if(player.Get_Exp() >= floor(10*(pow(player.Get_Level(),1.5)))){
        string skillget = "";

        //Calculate how many stats player gains and assign
        int HPUP = rand() % 2 + 3;
        int MPUP = rand() % 2 + 3;
        int AttackUP = rand() % 3+1;
        player.Set_Level(player.Get_Level() + 1);
        player.Set_HP(player.Get_HP()+HPUP);
        player.Set_MP(player.Get_MP()+MPUP);
        player.Set_Attack(player.Get_Attack()+AttackUP);
        player.Set_Defense(player.Get_Defense()+1);

        //Check for a skill @ new player level (skills are in Levelup_Skills[])
        if(Levelup_Skills[player.Get_Level()].Get_Name() != "Null"){
            player.Gain_Skill(Levelup_Skills[player.Get_Level()]);
            skillget = player.Get_Name()+" learns: "+Levelup_Skills[player.Get_Level()].Get_Name();
        }

        //output to adventure log
        string level_up_text = "LEVEL UP!  "+player.Get_Name()+" has obtained level "+to_string(player.Get_Level());
        DisplayToLog(level_up_text,logwin);
        level_up_text = "and gains: HP: "+to_string(HPUP)+" MP: "+to_string(MPUP)+" Attack: "+to_string(AttackUP)+" Def: 1";
        DisplayToLog(level_up_text,logwin);
        level_up_text = skillget;
        DisplayToLog(level_up_text,logwin);
        level_up_text = "HP/MP restored.";
        DisplayToLog(level_up_text,logwin);

        //Level up means free realestate heals
        player.Set_tmp_hp(player.Get_HP());
        player.Set_tmp_mp(player.Get_MP());

        //cout << level_up_text;
    }
}
void Rewards(Hero & player,Monster & enemy, WINDOW * logwin){
    //Get exp and gold
    player.Set_Gold_Count(player.Get_Gold_Count() + enemy.Get_Gold());
    player.Set_Exp(player.Get_Exp() + enemy.Get_Exp_Drop());

    //String to ouput to log
    string reward_string = player.Get_Name() +" receives: "+to_string(enemy.Get_Exp_Drop())+"exp, "+to_string(enemy.Get_Gold())+"gold";
    DisplayToLog(reward_string, logwin);

    //1% chance to get the item a monster was carrying
    if((rand() % 100) == 0){
        player.Gain_Item(enemy.Get_Drop());
        reward_string = player.Get_Name()+"found a: "+enemy.Get_Drop().Get_Name();
        DisplayToLog(reward_string, logwin);
    }

    //Check for levelup
    Level_Up(player,logwin);
    
    //cout << player.Get_Name() <<" receives:\n"<<to_string(enemy.Get_Exp_Drop())<<"exp\n"<<to_string(enemy.Get_Gold())<<"gold\n";
}
bool Combat_Loop(Hero &player,Monster enemy, WINDOW * logwin, WINDOW * controlswin, WINDOW * battlewin){
    //Flags and utility data declarations
    srand(time(NULL));
    bool chosen = false;
    bool proper_input = false;
    int command = -1;
    int calculation = 0;
    int move = 0;
    string player_move = "";
    string monster_move = "";
    string move_menu[10];

    player_move = enemy.Get_Name() + " draws near!";
    
    // display player_move to log window
    //DisplayToLog(player_move, logwin);
    DisplayToBattle(player_move, battlewin);
 
    //cout << enemy.Get_Name() << " draws near!"  << endl;
    while(player.Get_tmp_hp() > 0 && enemy.Get_tmp_hp() > 0){
        chosen = false;
        DisplayToBattle("",battlewin);
        player_move = player.Get_Name()+" HP: "+to_string(player.Get_tmp_hp())+" MP: "+to_string(player.Get_tmp_mp());
        DisplayToBattle(player_move, battlewin);
        DisplayToBattle("Command?",battlewin);
        //Player move <all cut out //player_move strings are for n-curses implimentation later
        while(!chosen){
            //Reject all but ints, can change later depending on n-curses menu design
            while(!proper_input){
                //cout << "HP: " << player.Get_tmp_hp() << " MP: " << player.Get_tmp_mp() << endl;

                //DisplayToLog(player_move, logwin);
                
                //cout << "Choose a move: \n";

                //Show all skills, add item skill to end for inventory?
                for(int i = 0; i < player.Get_Skill_Count(); i++){
                    move_menu[i] = to_string(i)+ " " + player.Get_Target_Skill(i).Get_Name();
                    
                    //DisplayToControls(move_menu, controlswin);

                    //cout << i << " " << player.Get_Target_Skill(i).Get_Name() << endl;
                }

                DisplayToControls(move_menu, controlswin);
                
                //keypad(logwin, true);

                keypad(logwin, true);
                command = wgetch(logwin) - 48; // 0 starts at value 48 for ncurses, this offset makes 0 equal 0, 1 equal 1, etc.
        
                //DisplayToLog(to_string(command), logwin);
                proper_input = true;
                keypad(logwin, false);

                /*
                cin >> command;
                if(!cin){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    //cout << "Improper input, numbers only.\n";
                }
                else{
                    proper_input = true;
                }
                */
            }
            proper_input = false;

            if(command <= player.Get_Skill_Count() && command >= 0){
                Skill & choice = player.Get_Target_Skill(command);
                switch(choice.Get_Type()){
                    case phys_attack:
                        player_move = player.Get_Name()+" "+choice.Get_Flavor();
                        
                        //DisplayToLog(player_move, logwin);
                        DisplayToBattle(player_move, battlewin);
                        
                        //cout << player.Get_Name()<<" "<<choice.Get_Flavor() << endl;
                        calculation = max(int(player.Get_Attack()*choice.Get_Modifier()-enemy.Get_Defense()),0);
                        player_move = enemy.Get_Name()+ " receives "+to_string(calculation)+" damage!";
                        
                        //DisplayToLog(player_move, logwin);
                        DisplayToBattle(player_move, battlewin);
                        
                        //cout << enemy.Get_Name() << " receives " << calculation << " damage!" << endl;
                        enemy.Set_tmp_hp(enemy.Get_tmp_hp() - calculation);
                        chosen = true;
                        break;
                
                    case magic_attack:
                        if(player.Get_tmp_mp() >= choice.Get_Cost()){
                            player_move = player.Get_Name()+" "+choice.Get_Flavor();
                
                            //DisplayToLog(player_move, logwin);
                            DisplayToBattle(player_move, battlewin);
                            
                            
                            //cout << player.Get_Name()<<" "<<choice.Get_Flavor() << endl;
                            calculation = player.Get_Attack()*choice.Get_Modifier()-enemy.Get_Defense();
                            player_move = enemy.Get_Name()+" receives "+to_string(calculation)+" damage!";
                
                            //DisplayToLog(player_move, logwin);
                            DisplayToBattle(player_move, battlewin);
                            
                            //cout << enemy.Get_Name() << " receives " << calculation << " damage!" << endl;
                            enemy.Set_tmp_hp(enemy.Get_tmp_hp() - calculation);
                            player.Set_tmp_mp(player.Get_tmp_mp()-choice.Get_Cost());
                            chosen = true;
                        }
                        else{
                            player_move = "Not enough MP";
                            //cout << "Not enough MP" << endl;
                
                            //DisplayToLog(player_move, logwin);
                            DisplayToBattle(player_move, battlewin);
                        }
                        break;
                
                    case healing:
                        if(player.Get_tmp_mp() >= choice.Get_Cost() && player.Get_tmp_hp() != player.Get_HP()){ 
                            calculation = min((player.Get_HP()-player.Get_tmp_hp()),int(choice.Get_Modifier()));
                            player_move = player.Get_Name()+" "+choice.Get_Flavor()+" "+to_string(calculation)+" HP recovered!";
                
                            //DisplayToLog(player_move, logwin);
                            DisplayToBattle(player_move, battlewin);
                            
                            //cout << player.Get_Name() << " " << choice.Get_Flavor()<< "\n" << calculation << "HP recovered!\n";
                            player.Set_tmp_hp(player.Get_tmp_hp()+calculation);
                
                            //DisplayToLog(player_move, logwin);
                            DisplayToBattle(player_move, battlewin);
                            
                            chosen = true;
                        }
                        else if(player.Get_tmp_mp() <= choice.Get_Cost()){
                            player_move = "Not enough MP";
                
                            //DisplayToLog(player_move, logwin);
                            DisplayToBattle(player_move, battlewin);
                            
                            //cout << "Not enough MP" << endl;
                        }
                        else{
                            player_move = "Hp is full";
                
                            //DisplayToLog(player_move, logwin);
                            DisplayToBattle(player_move, battlewin);
                            
                            //cout << "Hp is full" << endl;
                        }
                        break;                
                }
            }
            else{
                //cout << "Incorrect selection" << endl;

                //DisplayToLog("Incorrect selection", logwin);
            }
        }
        if(enemy.Get_tmp_hp() > 0){
            move = rand()% enemy.Get_Monster_Skill_Count();
            Skill monster_choice = enemy.Get_Monster_Skill(move);
            switch(monster_choice.Get_Type()){
                case phys_attack:
                    monster_move = enemy.Get_Name() + " " + monster_choice.Get_Flavor();
                    //cout << enemy.Get_Name() << " " << monster_choice.Get_Flavor() + "\n";
                
                    //DisplayToLog(monster_move, logwin);
                    DisplayToBattle(monster_move, battlewin);
                    
                    calculation = max(int(enemy.Get_Attack()*monster_choice.Get_Modifier() - player.Get_Defense()),0);
                    monster_move = player.Get_Name() + " receives "+to_string(calculation)+ " damage!";
                
                    //DisplayToLog(monster_move, logwin);
                    DisplayToLog(monster_move, battlewin);
                    
                    //cout << player.Get_Name() << " receives "<<to_string(calculation)<< " damage!\n";
                    player.Set_tmp_hp(player.Get_tmp_hp()-calculation);
                break;
                case magic_attack:
                    monster_move = enemy.Get_Name() + " " + monster_choice.Get_Flavor();
                    //cout << enemy.Get_Name() + " " << monster_choice.Get_Flavor() << "\n";
                    //DisplayToLog(monster_move, logwin);
                    DisplayToBattle(monster_move, battlewin);
                    
                    monster_move = player.Get_Name() + " receives " + to_string(monster_choice.Get_Modifier())+" damage!";
                    
                    //DisplayToLog(monster_move, logwin);
                    DisplayToBattle(monster_move, battlewin);
                    
                    //cout << player.Get_Name() << " receives " << to_string(monster_choice.Get_Modifier())<<" damage!\n";
                    player.Set_tmp_hp(player.Get_tmp_hp()-monster_choice.Get_Modifier());
                break;
                case healing:
                    calculation = min((enemy.Get_HP()-enemy.Get_tmp_hp()),int(monster_choice.Get_Modifier()));
                    monster_move = enemy.Get_Name()+" "+monster_choice.Get_Flavor()+" "+to_string(calculation)+" HP recovered!";
                    
                    //DisplayToLog(monster_move, logwin);
                    DisplayToBattle(monster_move, battlewin);
                    
                    //cout << enemy.Get_Name() << " " << monster_choice.Get_Flavor()<< "\n" << calculation << "HP recovered!\n";
                    enemy.Set_tmp_hp(enemy.Get_tmp_hp()+calculation);
                break;
            }
        }
    }
    //Impliment level_up function?
    if(player.Get_tmp_hp() > 0){
        player_move = player.Get_Name() + " has felled the " + enemy.Get_Name() + "!";
        //cout << player.Get_Name() << " has felled the " << enemy.Get_Name() << "!" << endl;
        
        //DisplayToLog(player_move, logwin);
        DisplayToBattle("",battlewin);
        DisplayToBattle(player_move, battlewin);
        DisplayToBattle("",battlewin);
        
        Rewards(player,enemy, logwin);
        return 1;
    }
    else{
        player_move = "Thou art dead";
        
        //DisplayToLog(player_move, logwin);
        DisplayToBattle(player_move, battlewin);
        
        return 0;

        //cout << "Thou art dead";
    }
}
