    //-------------------------------------------
    // Assignment ID: PROG8
    //
    // File name:     utilitybill.cpp
    //
    //
    // Purpose:   Write program to read data from a file named "kwhmeters.dat"
    //               and to write a formatted output report ("billing.log") 
    //               containing utility charges for customers in the intput file.
    //   Author: dgrant            
    //-------------------------------------------- 
    #include <fstream> 
    #include <iomanip> 
    #include <iostream> 
    #include <cstdlib> 
    #include <cmath>
    using namespace std;
    int main () 
    {
        string Cust_Name;

        long meter_before, 
             meter_after, 
             KWHused, 
             Tot_KWHused, 
             Avg_KWHused; 

        float Charge, 
              Tot_Charges, 
              Avg_Charges,
              valid_Records; 

                valid_Records = 0; 
                Tot_Charges = 0.00; 
                Tot_KWHused = 0.00; 
                Avg_Charges = 0.00; 
                Avg_KWHused = 0.00;  
            //-|--------------------------------------------------
            //-| Print the copyright notice declaring authorship.
            //-|-------------------------------------------------- 
                 cout << endl << "(c) 2017, dgrant De'Shon Grant " << endl << endl; 
            //-|----------------------------------------------------------
            //-|1.Open the input file 'kwhmeters.dat'.
            //-|        1.1 If a file-open error occurs
            //-|          1.1.1 Display message 
            //-|            "FATAL ERROR: Can not open file 'kwhmeters.dat'"
            //-|          1.1.2 Exit from program. 
            //-|-----------------------------------------------------------             
                ifstream inF; 

                inF.open ("kwhmeters.dat");

                    if(inF.fail()) {
                       cout << "FATAL ERROR: Can not open file 'kwhmeters.dat'" << endl;

                        exit(1);
                    }




              //---------------------------------------------------------
              //  2. Open the output file, and write the report captions. 
              //---------------------------------------------------------
                 ofstream outF; 
                outF.open("billing.log");

                outF << "===================" << endl;
                outF << "UTILITY BILLING LOG" << endl;
                outF << "SPRING 2017" << endl;
                outF << "===================" << endl;

                outF << "                        METER READINGS                " << endl;
                outF << "    CHARGE  KWH USED   CURRENT  PREVIOUS  CUSTOMER NAME" << endl;
                outF << "==========  ========  ========  ========  =================== " << endl;



            //-|------------------------------------------------------------  
            //-|        3. Repeat until all records have been read:
            //-|        3.1 Read usage record from the input file. 
            //-|        3.2 Compute KWH used (Current - Previous)
            //-|        3.3 If units used is valid (>=0)
            //-|            3.3.1 Increment count (valid_Records)
            //-|            3.3.2 Compute charge based on KWH used
            //-|            3.3.3 Update totals (Charges, KWHused).
            //-|            3.3.4 Write billing record to output file
            //-|        3.4 Else 
            //-|            3.4.1 Display bad meter reading message
            //-|            3.4.2 Write billing record to output file with
            //-|                  xx.xx and xxx for Charge and KWH Used.
            //-|        3.5 end Repeat
            //-|------------------------------------------------------------        
                   while(inF >> meter_before >> meter_after) {
                       inF.ignore(); 
                       getline(inF, Cust_Name); 
                        KWHused = meter_after - meter_before; 


                       if(KWHused >= 0){
                           valid_Records ++; 

                           if(KWHused >= 0 && KWHused < 501){
                              Charge = 53.00 + 0.200 * KWHused; 

                           } else if ( KWHused > 501 && KWHused < 1001){ 
                               Charge = 75.50 + 0.125 * KWHused;

                           } else if ( KWHused > 1001 && KWHused <= 3000){
                               Charge = 125.75 + 0.100 * KWHused ; 

                           } else {
                               Charge = 400.07 + 0.075 * KWHused ; 
                           }
                          Tot_Charges += Charge; 
                           Tot_KWHused += KWHused;  

                           outF << "$" << setw(9) << right << fixed << showpoint << setprecision(2) << Charge << "  "; 
                           outF << setw(8) << right << KWHused << "  " << setw(8) << setfill('0') << right << meter_after << setfill(' '); 
                           outF << "  " << setw(8) << setfill('0') <<  right << meter_before << setfill(' ') << "  " << setw(19) << left << Cust_Name << endl ; 

                       }
                      else{         cout << " BAD METER READING - old " << setw(8) << setfill('0') << meter_before << " new "  << setw(8) << meter_after << setfill(' ') << ' '  << Cust_Name << endl;
                           
                                    outF << "$" << setw(9) << right << fixed << showpoint << setprecision(2) << "xx.xx" << "  ";
                                    outF << setw(8) << right << "xxx" << "  " << setw(8) << setfill('0') << right << meter_after << setfill(' ') ;
                                    outF << "  " << setw(8) << setfill('0') <<  right << meter_before << setfill(' ') << "  " << setw(19) << left << Cust_Name << endl;
             
                             }  

                   }
                                    outF << "----------  --------  --------  --------  -------------------" << endl;

                 //-|--------------------------------------------------   
                 //-|   4. Write totals line (Tot_Charges, Tot_KWHUsed).
                 //-|-------------------------------------------------- 
               
                 outF << "$" << setw(9) << right << fixed << showpoint << setprecision(2) << Tot_Charges << "  " 
                      << setw(8) << right << Tot_KWHused << "  " << setw(8) << right << "        " 
                      << "  " << setw(8) <<  right << "        " << "  " << setw(19) << left << "TOTALS" << endl ; 

                 //-|--------------------------------------------------
                 //-|   6. Compute and write averages line (Avg_Charges, Avg_KWHUsed).
                 //-|-------------------------------------------------- 
                        Avg_Charges = Tot_Charges / valid_Records; 
                        Avg_KWHused = Tot_KWHused / valid_Records; 

                            outF << "$" << setw(9) << right << fixed << showpoint << setprecision(2) << Avg_Charges << "  " 
                                 << setw(8) << right << Avg_KWHused << "  " << setw(8) << right << "        " 
                                 << "  " << setw(8) <<  right << "        " << "  " << setw(19) << left << "AVERAGES" << endl ; 


                 //-|--------------------------------------------------   
                 //-|   5. Close input and output files.
                 //-|--------------------------------------------------   

           inF.close(); 
           outF.close();
        
 cout << endl << "(c) 2017, dgrant De'Shon Grant " << endl << endl; 
    
        return 0;
    }
