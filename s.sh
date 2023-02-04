#!/bin/bash
file_check() {
    if [ ! -f $1 ]; then
        echo ' il faut un fichier csv'
        return 1
    fi
    var=$1
    if [ ! "${var##*.}" = "csv" ]; then

        echo " the argument must be a csv file"
        return 1
    fi

    return 0

}
trait_argument_tab(){ 
    field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" check_field.csv) #find the field date in the input file
    field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" check_field.csv) #find the field coordonnees in the input file
    #---------------------------------------------------------------height------------------------------------------------------------------
    if [ $6 -eq 1 ]; then 

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" check_field.csv) #find the field station in the input file
        field_height=$(awk '{for(i=1;i<=NF;i++)if($i == "ALTITUDE")print i;}' FS=";" check_field.csv) #find the field altitude in the input file
        
        
        cut -d';' -f$field_station,$field_date,$field_coo,$field_height $1 >station_height0.csv #cut the input file to get the right field
        
        head -1 station_height0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" >field_number.csv #get the header of the new file
        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" field_number.csv) #find the field station in the new file
        field_height=$(awk '{for(i=1;i<=NF;i++)if($i == "ALTITUDE")print i;}' FS=";" field_number.csv) #find the field altitude in the new file
        field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv) #find the field date in the new file
        field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv) #find the field coordonnees in the new file
        rm field_number.csv
        
        tail +2 station_height0.csv | awk -v h=$field_height '{if($h != "" ) print $0;}' FS=";" >station_height.csv #remove the blank in the new file on the height field
        rm station_height0.csv #remove the file
        trait_argument_d_country $2 $3 $5 station_height.csv $field_date $field_coo #cut the new file according to the choice of the date or of the country by the user
       
        cut -d';' -f$field_station,$field_height,$field_coo cut_c.csv >station_height2.csv #cut the file after the cut of user and cut according to the sort

        rm cut_c.csv #remove the file
       
        ./exec station_height2.csv gnuplot_height.csv 3 2 3 #execute the programm
       
        rm station_height2.csv #remove the file
        
        gnuplot "height.gnu"
        eog "height.png" #avoid the warning
        rm gnuplot_height.csv
        
    fi

    field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" check_field.csv) #find the field date in the input file
    field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" check_field.csv) #find the field coordonnees in the input file
    #---------------------------------------moisture-------------------------------------------------------
    if [ $7 -eq 1 ]; then
        
        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" check_field.csv)
        field_moisture=$(awk '{for(i=1;i<=NF;i++)if($i == "HUMIDITÉ")print i;}' FS=";" check_field.csv)
        cut -d';' -f$field_station,$field_date,$field_moisture,$field_coo $1 >station_m0.csv

        head -1 station_m0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" >field_number.csv 

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" field_number.csv)
        field_moisture=$(awk '{for(i=1;i<=NF;i++)if($i == "HUMIDITÉ")print i;}' FS=";" field_number.csv)
        field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
        field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)
        rm field_number.csv

        tail +2 station_m0.csv | awk -v m=$field_moisture '{if($m != "" ) print $0;}' FS=";" >station_m.csv
        rm station_m0.csv
        trait_argument_d_country $2 $3 $5 station_m.csv $field_date $field_coo

        cut -d';' -f$field_station,$field_moisture,$field_coo cut_c.csv >station_m2.csv

        rm cut_c.csv
        ./exec station_m2.csv station_m.csv 7 2 3 1
        
        rm station_m2.csv
        
        ./exec station_m.csv gnuplot_m.csv 7 2 3 0
        
        rm station_m.csv

        gnuplot "moisture.gnu"
        eog "moisture.png" &2>/dev/null
        rm gnuplot_m.csv

    fi
    field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" check_field.csv) #find the field date in the input file
    field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" check_field.csv) #find the field coordonnees in the input file
     #---------------------------------------------------------------wind------------------------------------------------------------------
    if [ $8 -eq 1 ]; then

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" check_field.csv)
        field_wind1=$(awk '{for(i=1;i<=NF;i++)if($i == "DIRECTIONDUVENTMOYEN10MN")print i;}' FS=";" check_field.csv)
        field_wind2=$(awk '{for(i=1;i<=NF;i++)if($i == "VITESSEDUVENTMOYEN10MN")print i;}' FS=";" check_field.csv)
        cut -d';' -f$field_station,$field_date,$field_wind1,$field_wind2,$field_coo $1 >station_wind0.csv

        head -1 station_wind0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" >field_number.csv 

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" field_number.csv)
        field_wind1=$(awk '{for(i=1;i<=NF;i++)if($i == "DIRECTIONDUVENTMOYEN10MN")print i;}' FS=";" field_number.csv)
        field_wind2=$(awk '{for(i=1;i<=NF;i++)if($i == "VITESSEDUVENTMOYEN10MN")print i;}' FS=";" field_number.csv)
        field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
        field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)
        rm field_number.csv

        tail +2 station_wind0.csv | awk -v w=$field_wind1 -v w2=$field_wind2 '{if($w != "" && $w2 != "" )  print $0;}' FS=";" >station_wind.csv
        rm station_wind0.csv
        trait_argument_d_country $2 $3 $5 station_wind.csv $field_date $field_coo

        cut -d';' -f$field_station,$field_wind1,$field_wind2,$field_coo cut_c.csv >station_wind2.csv

        rm cut_c.csv
       
        ./exec station_wind2.csv gnuplot_wind.csv 2 1 3
      
        rm station_wind2.csv
        gnuplot "wind.gnu"
        eog "wind.png" &2>/dev/null
        rm gnuplot_wind.csv
    fi
    field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" check_field.csv) #find the field date in the input file
    field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" check_field.csv) #find the field coordonnees in the input file
    #---------------------------------------------------------------pressure mode 1------------------------------------------------------------------
    if [ $9 -eq 1 ]; then

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" check_field.csv)
        field_pressure=$(awk '{for(i=1;i<=NF;i++)if($i == "PRESSIONSTATION")print i;}' FS=";" check_field.csv)

        cut -d";" -f$field_station,$field_date,$field_pressure,$field_coo $1 >station_pres_ave0.csv

        head -1 station_pres_ave0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" >field_number.csv 

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" field_number.csv)
        field_pressure=$(awk '{for(i=1;i<=NF;i++)if($i == "PRESSIONSTATION")print i;}' FS=";" field_number.csv)
        field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
        field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)
        rm field_number.csv

        tail +2 station_pres_ave0.csv | awk -v ave=$field_pressure '{if($ave != "" ) print $0;}' FS=";" >station_pres_ave.csv
        rm station_pres_ave0.csv
        trait_argument_d_country $2 $3 $5 station_pres_ave.csv $field_date $field_coo

        cut -d';' -f$field_station,$field_pressure cut_c.csv >station_pres_ave2.csv

        rm cut_c.csv
     
        
        ./exec station_pres_ave2.csv gnuplot_pres_max.csv 1 1 3
          
        
        rm station_pres_ave2.csv

        
        gnuplot "p1Tab.gnu"
        eog "p1Tab.png" &2>/dev/null
       
        rm gnuplot_pres_max.csv
    fi
    field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" check_field.csv) #find the field date in the input file
    field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" check_field.csv) #find the field coordonnees in the input file
    #---------------------------------------------------------------temperature mode 1------------------------------------------------------------------
    if [ ${@: -1} -eq 1 ]; then

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" check_field.csv)
        field_temp=$(awk '{for(i=1;i<=NF;i++)if($i == "TEMPÉRATURE(°C)")print i;}' FS=";" check_field.csv)
        cut -d";" -f$field_station,$field_date,$field_coo,$field_temp $1 >station_temp_ave0.csv

        head -1 station_temp_ave0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" >field_number.csv 

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" field_number.csv)
        field_temp=$(awk '{for(i=1;i<=NF;i++)if($i == "TEMPÉRATURE(°C)")print i;}' FS=";" field_number.csv)

        field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
        field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)
        rm field_number.csv

        tail +2 station_temp_ave0.csv | awk -v ave=$field_temp '{if($ave != "" ) print $0;}' FS=";" >station_temp_ave.csv
        rm station_temp_ave0.csv

        trait_argument_d_country $2 $3 $5 station_temp_ave.csv $field_date $field_coo
        cut -d';' -f$field_station,$field_temp cut_c.csv >station_temp_ave2.csv
        rm cut_c.csv
      
        ./exec station_temp_ave2.csv gnuplot_temp_max.csv 1 1 3
      
        
        rm station_temp_ave2.csv

        gnuplot "t1Tab.gnu"
        eog "t1Tab.png" &2>/dev/null
       
        rm gnuplot_temp_max.csv
        
    fi
}
trait_argument_abr() {

    field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" check_field.csv) #find the field date in the input file
    field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" check_field.csv) #find the field coordonnees in the input file

    #---------------------------------------------------------------height------------------------------------------------------------------
    if [ $6 -eq 1 ]; then 

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" check_field.csv) #find the field station in the input file
        field_height=$(awk '{for(i=1;i<=NF;i++)if($i == "ALTITUDE")print i;}' FS=";" check_field.csv) #find the field altitude in the input file

        cut -d';' -f$field_station,$field_date,$field_coo,$field_height $1 >station_height0.csv #cut the input file to get the right field

        head -1 station_height0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" >field_number.csv #get the header of the new file
        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" field_number.csv) #find the field station in the new file
        field_height=$(awk '{for(i=1;i<=NF;i++)if($i == "ALTITUDE")print i;}' FS=";" field_number.csv) #find the field altitude in the new file
        field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv) #find the field date in the new file
        field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv) #find the field coordonnees in the new file
        rm field_number.csv

        tail +2 station_height0.csv | awk -v h=$field_height '{if($h != "" ) print $0;}' FS=";" >station_height.csv #remove the blank in the new file on the height field
        rm station_height0.csv #remove the file
        trait_argument_d_country $2 $3 $5 station_height.csv $field_date $field_coo #cut the new file according to the choice of the date or of the country by the user

        cut -d';' -f$field_station,$field_height,$field_coo cut_c.csv >station_height2.csv #cut the file after the cut of user and cut according to the sort

        rm cut_c.csv #remove the file
        if [ $4 -eq 1 ]; then #if the user choice reverse
            ./exec station_height2.csv gnuplot_height.csv 4 1 2
        else
            ./exec station_height2.csv gnuplot_height.csv 4 2 2 #execute the programm
        fi
        rm station_height2.csv #remove the file

        gnuplot "height.gnu"
        eog "height.png" &2>/dev/null #avoid the warning
        rm gnuplot_height.csv
    fi
    field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" check_field.csv) #find the field date in the input file
    field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" check_field.csv) #find the field coordonnees in the input file
    #---------------------------------------------------------------moisture------------------------------------------------------------------
    if [ $7 -eq 1 ]; then

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" check_field.csv)
        field_moisture=$(awk '{for(i=1;i<=NF;i++)if($i == "HUMIDITÉ")print i;}' FS=";" check_field.csv)
        cut -d';' -f$field_station,$field_date,$field_moisture,$field_coo $1 >station_m0.csv

        head -1 station_m0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" >field_number.csv

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" field_number.csv)
        field_moisture=$(awk '{for(i=1;i<=NF;i++)if($i == "HUMIDITÉ")print i;}' FS=";" field_number.csv)
        field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
        field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)
        rm field_number.csv

        tail +2 station_m0.csv | awk -v m=$field_moisture '{if($m != "" ) print $0;}' FS=";" >station_m.csv
        rm station_m0.csv
        trait_argument_d_country $2 $3 $5 station_m.csv $field_date $field_coo

        cut -d';' -f$field_station,$field_moisture,$field_coo cut_c.csv >station_m2.csv

        rm cut_c.csv
        if [ $4 -eq 1 ]; then
            ./exec station_m2.csv station_m.csv 7 1 2 1 #execute the programm in the fisrt time to have the max of the station
        else
            ./exec station_m2.csv station_m.csv 7 2 2 1
        fi
        rm station_m2.csv
        if [ $4 -eq 1 ]; then
            ./exec station_m.csv gnuplot_m.csv 7 1 2 0 #execute the programm in the second time with the output of the first programm to sort the avl
        else
            ./exec station_m.csv gnuplot_m.csv 7 2 2 0
        fi
        rm station_m.csv

        gnuplot "moisture.gnu"
        eog "moisture.png" & 2 >/dev/null
        rm gnuplot_m.csv

    fi
    field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" check_field.csv) #find the field date in the input file
    field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" check_field.csv) #find the field coordonnees in the input file
     #---------------------------------------------------------------wind------------------------------------------------------------------
    if [ $8 -eq 1 ]; then

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" check_field.csv)
        field_wind1=$(awk '{for(i=1;i<=NF;i++)if($i == "DIRECTIONDUVENTMOYEN10MN")print i;}' FS=";" check_field.csv)
        field_wind2=$(awk '{for(i=1;i<=NF;i++)if($i == "VITESSEDUVENTMOYEN10MN")print i;}' FS=";" check_field.csv)
        cut -d';' -f$field_station,$field_date,$field_wind1,$field_wind2,$field_coo $1 >station_wind0.csv

        head -1 station_wind0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" >field_number.csv 

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" field_number.csv)
        field_wind1=$(awk '{for(i=1;i<=NF;i++)if($i == "DIRECTIONDUVENTMOYEN10MN")print i;}' FS=";" field_number.csv)
        field_wind2=$(awk '{for(i=1;i<=NF;i++)if($i == "VITESSEDUVENTMOYEN10MN")print i;}' FS=";" field_number.csv)
        field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
        field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)
        rm field_number.csv

        tail +2 station_wind0.csv | awk -v w=$field_wind1 -v w2=$field_wind2 '{if($w != "" && $w2 != "" )  print $0;}' FS=";" >station_wind.csv
        rm station_wind0.csv
        trait_argument_d_country $2 $3 $5 station_wind.csv $field_date $field_coo

        cut -d';' -f$field_station,$field_wind1,$field_wind2,$field_coo cut_c.csv >station_wind2.csv

        rm cut_c.csv
         if [ $4 -eq 1 ]; then
            ./exec station_wind2.csv gnuplot_wind.csv 8 2 2
        else
            ./exec station_wind2.csv gnuplot_wind.csv 8 1 2
        fi
        rm station_wind2.csv
        gnuplot "wind.gnu"
        eog "wind.png" &2>/dev/null
        rm gnuplot_wind.csv
    fi
    field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" check_field.csv) #find the field date in the input file
    field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" check_field.csv) #find the field coordonnees in the input file
    #---------------------------------------------------------------pressure mode 1------------------------------------------------------------------
    if [ $9 -eq 1 ]; then

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" check_field.csv)
        field_pressure=$(awk '{for(i=1;i<=NF;i++)if($i == "PRESSIONSTATION")print i;}' FS=";" check_field.csv)

        cut -d";" -f$field_station,$field_date,$field_pressure,$field_coo $1 >station_pres_ave0.csv

        head -1 station_pres_ave0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" >field_number.csv 

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" field_number.csv)
        field_pressure=$(awk '{for(i=1;i<=NF;i++)if($i == "PRESSIONSTATION")print i;}' FS=";" field_number.csv)
        field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
        field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)
        rm field_number.csv

        tail +2 station_pres_ave0.csv | awk -v ave=$field_pressure '{if($ave != "" ) print $0;}' FS=";" >station_pres_ave.csv
        rm station_pres_ave0.csv
        trait_argument_d_country $2 $3 $5 station_pres_ave.csv $field_date $field_coo

        cut -d';' -f$field_station,$field_pressure cut_c.csv >station_pres_ave2.csv

        rm cut_c.csv
        if [ $4 -eq 1 ]; then
            ./exec station_pres_ave2.csv gnuplot_pres_ave.csv 3 2 2
            ./exec station_pres_ave2.csv gnuplot_pres_min.csv 2 2 2
            ./exec station_pres_ave2.csv gnuplot_pres_max.csv 1 2 2

        else
            ./exec station_pres_ave2.csv gnuplot_pres_ave.csv 3 1 2
            ./exec station_pres_ave2.csv gnuplot_pres_min.csv 2 1 2
            ./exec station_pres_ave2.csv gnuplot_pres_max.csv 1 1 2
          
        fi
        rm station_pres_ave2.csv

        
        gnuplot "p1.gnu"
        eog "p1.png" &2>/dev/null
        rm gnuplot_pres_ave.csv
        rm gnuplot_pres_min.csv
        rm gnuplot_pres_max.csv
    
    #---------------------------------------------------------------pressure mode 2------------------------------------------------------------------
    elif [ $9 -eq 2 ]; then
        field_pressure=$(awk '{for(i=1;i<=NF;i++)if($i == "PRESSIONSTATION")print i;}' FS=";" check_field.csv)

        cut -d";" -f$field_date,$field_pressure,$field_coo $1 >pres_date0.csv

        head -1 pres_date0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" >field_number.csv 

        field_pressure=$(awk '{for(i=1;i<=NF;i++)if($i == "PRESSIONSTATION")print i;}' FS=";" field_number.csv)
        field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
        field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)

        tail +2 pres_date0.csv | awk -v p=$field_pressure '{if($p != "" ) print $0;}' FS=";" >pres_date.csv
        rm pres_date0.csv

        trait_argument_d_country $2 $3 $5 pres_date.csv $field_date $field_coo

        rm field_number.csv

        cut -d';' -f$field_pressure,$field_date cut_c.csv >pres_date2.csv
        rm cut_c.csv

        awk '{split($1,ddate,"T") ; split(ddate[1],fdate,"-"); split(ddate[2],hdate,":"); if(hdate[1] < 10) hdate[1]=sprintf("0%d", hdate[1]);  all=sprintf("%d%s%s%s", fdate[1], fdate[2], fdate[3], hdate[1]);   print all";"$2;}' FS=";" pres_date2.csv >c_date.csv #cut les dates
        rm pres_date2.csv
        if [ $4 -eq 1 ]; then
            ./exec c_date.csv gnuplot_pres_date.csv 5 2 2
        else
            ./exec c_date.csv gnuplot_pres_date.csv 5 1 2
        fi
        rm c_date.csv

        gnuplot "p2.gnu"
        eog "p2.png" &2>/dev/null
        rm gnuplot_pres_date.csv
    
    #---------------------------------------------------------------pressure mode 3------------------------------------------------------------------
    elif [ $9 -eq 3 ]; then

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" check_field.csv)
        field_pressure=$(awk '{for(i=1;i<=NF;i++)if($i == "PRESSIONSTATION")print i;}' FS=";" check_field.csv)

        cut -d";" -f$field_station,$field_date,$field_pressure,$field_coo $1 >station_pres_date0.csv

        head -1 station_pres_date0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" >field_number.csv

        field_pressure=$(awk '{for(i=1;i<=NF;i++)if($i == "PRESSIONSTATION")print i;}' FS=";" field_number.csv)
        field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
        field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)
        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" field_number.csv)
        rm field_number.csv

        tail +2 station_pres_date0.csv | awk -v p=$field_pressure '{if($p != "" ) print $0;}' FS=";" >station_pres_date.csv
        rm station_pres_date0.csv

        trait_argument_d_country $2 $3 $5 station_pres_date.csv $field_date $field_coo

        cut -d';' -f$field_pressure,$field_date,$field_station cut_c.csv >station_pres_date2.csv
        rm cut_c.csv

        awk '{split($2,ddate,"T") ; split(ddate[1],fdate,"-"); split(ddate[2],hdate,":"); if(hdate[1] < 10) hdate[1]=sprintf("0%d", hdate[1]);  all=sprintf("%d%s%s%s", fdate[1], fdate[2], fdate[3], hdate[1]);   print $1";"all";"$3;}' FS=";" station_pres_date2.csv >pres_date3.csv

        rm station_pres_date2.csv
         if [ $4 -eq 1 ]; then
            ./exec pres_date3.csv gnuplot_station_pres_date.csv 6 2 2
        else
            ./exec pres_date3.csv gnuplot_station_pres_date.csv 6 1 2
        fi
        rm pres_date3.csv
        gnuplot "p3.gnu"
        eog "p3.png" 2 >/dev/null
        rm gnuplot_station_pres_date.csv
    fi
    field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" check_field.csv) #find the field date in the input file
    field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" check_field.csv) #find the field coordonnees in the input file
    #---------------------------------------------------------------temperature mode 1------------------------------------------------------------------
    if [ ${@: -1} -eq 1 ]; then

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" check_field.csv)
        field_temp=$(awk '{for(i=1;i<=NF;i++)if($i == "TEMPÉRATURE(°C)")print i;}' FS=";" check_field.csv)
        cut -d";" -f$field_station,$field_date,$field_coo,$field_temp $1 >station_temp_ave0.csv

        head -1 station_temp_ave0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" >field_number.csv 

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" field_number.csv)
        field_temp=$(awk '{for(i=1;i<=NF;i++)if($i == "TEMPÉRATURE(°C)")print i;}' FS=";" field_number.csv)

        field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
        field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)
        rm field_number.csv

        tail +2 station_temp_ave0.csv | awk -v ave=$field_temp '{if($ave != "" ) print $0;}' FS=";" >station_temp_ave.csv
        rm station_temp_ave0.csv

        trait_argument_d_country $2 $3 $5 station_temp_ave.csv $field_date $field_coo
        cut -d';' -f$field_station,$field_temp cut_c.csv >station_temp_ave2.csv
        rm cut_c.csv
        if [ $4 -eq 1 ]; then
            ./exec station_temp_ave2.csv gnuplot_temp_ave.csv 3 2 2
            ./exec station_temp_ave2.csv gnuplot_temp_min.csv 2 2 2
            ./exec station_temp_ave2.csv gnuplot_temp_max.csv 1 2 2
        else
            ./exec station_temp_ave2.csv gnuplot_temp_ave.csv 3 1 2
            ./exec station_temp_ave2.csv gnuplot_temp_min.csv 2 1 2
            ./exec station_temp_ave2.csv gnuplot_temp_max.csv 1 1 2
        fi

        rm station_temp_ave2.csv

         gnuplot "t1.gnu"
        eog "t1.png" &2>/dev/null
        rm gnuplot_temp_ave.csv
        rm gnuplot_temp_min.csv
        rm gnuplot_temp_max.csv
    
    #---------------------------------------------------------------temperature mode 2------------------------------------------------------------------
    elif [ ${@: -1} -eq 2 ]; then
        field_temp=$(awk '{for(i=1;i<=NF;i++)if($i == "TEMPÉRATURE(°C)")print i;}' FS=";" check_field.csv)
        cut -d";" -f$field_date,$field_temp,$field_coo $1 >temp_date0.csv

        head -1 temp_date0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" >field_number.csv 

        field_temp=$(awk '{for(i=1;i<=NF;i++)if($i == "TEMPÉRATURE(°C)")print i;}' FS=";" field_number.csv)
        field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
        field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)

        tail +2 temp_date0.csv | awk -v t=$field_temp '{if($t != "" ) print $0;}' FS=";" >temp_date.csv
        rm temp_date0.csv

        trait_argument_d_country $2 $3 $5 temp_date.csv $field_date $field_coo

        rm field_number.csv

        cut -d';' -f$field_temp,$field_date cut_c.csv >temp_date2.csv
        rm cut_c.csv

        awk '{split($1,ddate,"T") ; split(ddate[1],fdate,"-"); split(ddate[2],hdate,":"); if(hdate[1] < 10) hdate[1]=sprintf("0%d", hdate[1]);  all=sprintf("%d%s%s%s", fdate[1], fdate[2], fdate[3], hdate[1]);   print all";"$2;}' FS=";" temp_date2.csv >c_date.csv #concaténer
        rm temp_date2.csv
        if [ $4 -eq 1 ]; then
            ./exec c_date.csv gnuplot_temp_date.csv 5 2 2
        else
            ./exec c_date.csv gnuplot_temp_date.csv 5 1 2
        fi
        rm c_date.csv
        gnuplot "t2.gnu"
        eog "t2.png" &2>/dev/null
        rm gnuplot_temp_date.csv
    
    #---------------------------------------------------------------temperature mode 3------------------------------------------------------------------ 
    elif [ ${@: -1} -eq 3 ]; then

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" check_field.csv)
        field_temp=$(awk '{for(i=1;i<=NF;i++)if($i == "TEMPÉRATURE(°C)")print i;}' FS=";" check_field.csv)

        cut -d";" -f$field_station,$field_date,$field_temp,$field_coo $1 >station_temp_date0.csv

        head -1 station_temp_date0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" >field_number.csv

        field_temp=$(awk '{for(i=1;i<=NF;i++)if($i == "TEMPÉRATURE(°C)")print i;}' FS=";" field_number.csv)
        field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
        field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)
        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" field_number.csv)
        rm field_number.csv

        tail +2 station_temp_date0.csv | awk -v t=$field_temp '{if($t != "" ) print $0;}' FS=";" >station_temp_date.csv
        rm station_temp_date0.csv

        trait_argument_d_country $2 $3 $5 station_temp_date.csv $field_date $field_coo

        cut -d';' -f$field_temp,$field_date,$field_station cut_c.csv >station_temp_date2.csv
        rm cut_c.csv

        awk '{split($2,ddate,"T") ; split(ddate[1],fdate,"-"); split(ddate[2],hdate,":"); if(hdate[1] < 10) hdate[1]=sprintf("0%d", hdate[1]);  all=sprintf("%d%s%s%s", fdate[1], fdate[2], fdate[3], hdate[1]);   print $1";"all";"$3;}' FS=";" station_temp_date2.csv >temp_date3.csv
        rm station_temp_date2.csv
        if [ $4 -eq 1 ]; then
            ./exec temp_date3.csv gnuplot_station_temp_date.csv 6 2 2
        else
            ./exec temp_date3.csv gnuplot_station_temp_date.csv 6 1 2
        fi
        rm temp_date3.csv
           gnuplot "t3.gnu"
        eog "t3.png" &2>/dev/null
        rm gnuplot_station_temp_date.csv

    fi

}

trait_argument_avl() {

    field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" check_field.csv) #find the field date in the input file
    field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" check_field.csv) #find the field coordonnees in the input file

    #---------------------------------------------------------------height------------------------------------------------------------------
    if [ $6 -eq 1 ]; then 

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" check_field.csv) #find the field station in the input file
        field_height=$(awk '{for(i=1;i<=NF;i++)if($i == "ALTITUDE")print i;}' FS=";" check_field.csv) #find the field altitude in the input file

        cut -d';' -f$field_station,$field_date,$field_coo,$field_height $1 >station_height0.csv #cut the input file to get the right field

        head -1 station_height0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" >field_number.csv #get the header of the new file
        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" field_number.csv) #find the field station in the new file
        field_height=$(awk '{for(i=1;i<=NF;i++)if($i == "ALTITUDE")print i;}' FS=";" field_number.csv) #find the field altitude in the new file
        field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv) #find the field date in the new file
        field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv) #find the field coordonnees in the new file
        rm field_number.csv

        tail +2 station_height0.csv | awk -v h=$field_height '{if($h != "" ) print $0;}' FS=";" >station_height.csv #remove the blank in the new file on the height field
        rm station_height0.csv #remove the file
        trait_argument_d_country $2 $3 $5 station_height.csv $field_date $field_coo #cut the new file according to the choice of the date or of the country by the user

        cut -d';' -f$field_station,$field_height,$field_coo cut_c.csv >station_height2.csv #cut the file after the cut of user and cut according to the sort

        rm cut_c.csv #remove the file
        if [ $4 -eq 1 ]; then #if the user choice reverse
            ./exec station_height2.csv gnuplot_height.csv 4 1 1
        else
            ./exec station_height2.csv gnuplot_height.csv 4 2 1 #execute the programm
        fi
        rm station_height2.csv #remove the file

         gnuplot "height.gnu"
        eog "height.png" &2>/dev/null #avoid the warning
        rm gnuplot_height.csv
    fi
    field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" check_field.csv) #find the field date in the input file
    field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" check_field.csv) #find the field coordonnees in the input file
    #---------------------------------------------------------------moisture------------------------------------------------------------------
    if [ $7 -eq 1 ]; then

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" check_field.csv)
        field_moisture=$(awk '{for(i=1;i<=NF;i++)if($i == "HUMIDITÉ")print i;}' FS=";" check_field.csv)
        cut -d';' -f$field_station,$field_date,$field_moisture,$field_coo $1 >station_m0.csv

        head -1 station_m0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" >field_number.csv 

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" field_number.csv)
        field_moisture=$(awk '{for(i=1;i<=NF;i++)if($i == "HUMIDITÉ")print i;}' FS=";" field_number.csv)
        field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
        field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)
        rm field_number.csv

        tail +2 station_m0.csv | awk -v m=$field_moisture '{if($m != "" ) print $0;}' FS=";" >station_m.csv
        rm station_m0.csv
        trait_argument_d_country $2 $3 $5 station_m.csv $field_date $field_coo

        cut -d';' -f$field_station,$field_moisture,$field_coo cut_c.csv >station_m2.csv

        rm cut_c.csv
        if [ $4 -eq 1 ]; then
            ./exec station_m2.csv station_m.csv 7 1 1 1 #execute the programm in the fisrt time to have the max of the station
        else
            ./exec station_m2.csv station_m.csv 7 2 1 1
        fi
        rm station_m2.csv
        if [ $4 -eq 1 ]; then
            ./exec station_m.csv gnuplot_m.csv 7 1 1 0 #execute the programm in the second time with the output of the first programm to sort the avl
        else
            ./exec station_m.csv gnuplot_m.csv 7 2 1 0
        fi
        rm station_m.csv

       gnuplot "moisture.gnu"
        eog "moisture.png" &2>/dev/null
        rm gnuplot_m.csv

    fi
    field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" check_field.csv) #find the field date in the input file
    field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" check_field.csv) #find the field coordonnees in the input file
     #---------------------------------------------------------------wind------------------------------------------------------------------
    if [ $8 -eq 1 ]; then

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" check_field.csv)
        field_wind1=$(awk '{for(i=1;i<=NF;i++)if($i == "DIRECTIONDUVENTMOYEN10MN")print i;}' FS=";" check_field.csv)
        field_wind2=$(awk '{for(i=1;i<=NF;i++)if($i == "VITESSEDUVENTMOYEN10MN")print i;}' FS=";" check_field.csv)
        cut -d';' -f$field_station,$field_date,$field_wind1,$field_wind2,$field_coo $1 >station_wind0.csv

        head -1 station_wind0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" >field_number.csv 

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" field_number.csv)
        field_wind1=$(awk '{for(i=1;i<=NF;i++)if($i == "DIRECTIONDUVENTMOYEN10MN")print i;}' FS=";" field_number.csv)
        field_wind2=$(awk '{for(i=1;i<=NF;i++)if($i == "VITESSEDUVENTMOYEN10MN")print i;}' FS=";" field_number.csv)
        field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
        field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)
        rm field_number.csv

        tail +2 station_wind0.csv | awk -v w=$field_wind1 -v w2=$field_wind2 '{if($w != "" && $w2 != "" )  print $0;}' FS=";" >station_wind.csv
        rm station_wind0.csv
        trait_argument_d_country $2 $3 $5 station_wind.csv $field_date $field_coo

        cut -d';' -f$field_station,$field_wind1,$field_wind2,$field_coo cut_c.csv >station_wind2.csv

        rm cut_c.csv
         if [ $4 -eq 1 ]; then
            ./exec station_wind2.csv gnuplot_wind.csv 8 2 1
        else
            ./exec station_wind2.csv gnuplot_wind.csv 8 1 1
        fi
        rm station_wind2.csv
        gnuplot "wind.gnu"
        eog "wind.png" &2>/dev/null
        rm gnuplot_wind.csv
    fi
    field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" check_field.csv) #find the field date in the input file
    field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" check_field.csv) #find the field coordonnees in the input file
    #---------------------------------------------------------------pressure mode 1------------------------------------------------------------------
    if [ $9 -eq 1 ]; then

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" check_field.csv)
        field_pressure=$(awk '{for(i=1;i<=NF;i++)if($i == "PRESSIONSTATION")print i;}' FS=";" check_field.csv)

        cut -d";" -f$field_station,$field_date,$field_pressure,$field_coo $1 >station_pres_ave0.csv

        head -1 station_pres_ave0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" >field_number.csv 

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" field_number.csv)
        field_pressure=$(awk '{for(i=1;i<=NF;i++)if($i == "PRESSIONSTATION")print i;}' FS=";" field_number.csv)
        field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
        field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)
        rm field_number.csv

        tail +2 station_pres_ave0.csv | awk -v ave=$field_pressure '{if($ave != "" ) print $0;}' FS=";" >station_pres_ave.csv
        rm station_pres_ave0.csv
        trait_argument_d_country $2 $3 $5 station_pres_ave.csv $field_date $field_coo

        cut -d';' -f$field_station,$field_pressure cut_c.csv >station_pres_ave2.csv

        rm cut_c.csv
        if [ $4 -eq 1 ]; then
            ./exec station_pres_ave2.csv gnuplot_pres_ave.csv 3 2 1
            ./exec station_pres_ave2.csv gnuplot_pres_min.csv 2 2 1
            ./exec station_pres_ave2.csv gnuplot_pres_max.csv 1 2 1
        else
            ./exec station_pres_ave2.csv gnuplot_pres_ave.csv 3 1 2
            ./exec station_pres_ave2.csv gnuplot_pres_min.csv 2 1 2
            ./exec station_pres_ave2.csv gnuplot_pres_max.csv 1 1 2
           
        fi
        rm station_pres_ave2.csv

         gnuplot "p1.gnu"
        eog "p1.png" &2>/dev/null
        rm gnuplot_pres_ave.csv
        rm gnuplot_pres_min.csv
        rm gnuplot_pres_max.csv
    
    #---------------------------------------------------------------pressure mode 2------------------------------------------------------------------
    elif [ $9 -eq 2 ]; then
        field_pressure=$(awk '{for(i=1;i<=NF;i++)if($i == "PRESSIONSTATION")print i;}' FS=";" check_field.csv)

        cut -d";" -f$field_date,$field_pressure,$field_coo $1 >pres_date0.csv

        head -1 pres_date0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" >field_number.csv 

        field_pressure=$(awk '{for(i=1;i<=NF;i++)if($i == "PRESSIONSTATION")print i;}' FS=";" field_number.csv)
        field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
        field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)

        tail +2 pres_date0.csv | awk -v p=$field_pressure '{if($p != "" ) print $0;}' FS=";" >pres_date.csv
        rm pres_date0.csv

        trait_argument_d_country $2 $3 $5 pres_date.csv $field_date $field_coo

        rm field_number.csv

        cut -d';' -f$field_pressure,$field_date cut_c.csv >pres_date2.csv
        rm cut_c.csv

        awk '{split($1,ddate,"T") ; split(ddate[1],fdate,"-"); split(ddate[2],hdate,":"); if(hdate[1] < 10) hdate[1]=sprintf("0%d", hdate[1]);  all=sprintf("%d%s%s%s", fdate[1], fdate[2], fdate[3], hdate[1]);   print all";"$2;}' FS=";" pres_date2.csv >c_date.csv #cut les dates
        rm pres_date2.csv
        if [ $4 -eq 1 ]; then
            ./exec c_date.csv gnuplot_pres_date.csv 5 2 1
        else
            ./exec c_date.csv gnuplot_pres_date.csv 5 1 1
        fi
        rm c_date.csv

        gnuplot "p2.gnu"
        eog "p2.png" &2>/dev/null
        rm gnuplot_pres_date.csv
    
    #---------------------------------------------------------------pressure mode 3------------------------------------------------------------------
    elif [ $9 -eq 3 ]; then

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" check_field.csv)
        field_pressure=$(awk '{for(i=1;i<=NF;i++)if($i == "PRESSIONSTATION")print i;}' FS=";" check_field.csv)

        cut -d";" -f$field_station,$field_date,$field_pressure,$field_coo $1 >station_pres_date0.csv

        head -1 station_pres_date0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" >field_number.csv

        field_pressure=$(awk '{for(i=1;i<=NF;i++)if($i == "PRESSIONSTATION")print i;}' FS=";" field_number.csv)
        field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
        field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)
        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" field_number.csv)
        rm field_number.csv

        tail +2 station_pres_date0.csv | awk -v p=$field_pressure '{if($p != "" ) print $0;}' FS=";" >station_pres_date.csv
        rm station_pres_date0.csv

        trait_argument_d_country $2 $3 $5 station_pres_date.csv $field_date $field_coo

        cut -d';' -f$field_pressure,$field_date,$field_station cut_c.csv >station_pres_date2.csv
        rm cut_c.csv

        awk '{split($2,ddate,"T") ; split(ddate[1],fdate,"-"); split(ddate[2],hdate,":"); if(hdate[1] < 10) hdate[1]=sprintf("0%d", hdate[1]);  all=sprintf("%d%s%s%s", fdate[1], fdate[2], fdate[3], hdate[1]);   print $1";"all";"$3;}' FS=";" station_pres_date2.csv >pres_date3.csv

        rm station_pres_date2.csv
         if [ $4 -eq 1 ]; then
            ./exec pres_date3.csv gnuplot_station_pres_date.csv 6 2 1
        else
            ./exec pres_date3.csv gnuplot_station_pres_date.csv 6 1 1
        fi
        rm pres_date3.csv
        
           gnuplot "p3.gnu"
        eog "p3.png" &2>/dev/null
        rm gnuplot_station_pres_date.csv
    fi
    field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" check_field.csv) #find the field date in the input file
    field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" check_field.csv) #find the field coordonnees in the input file
    #---------------------------------------------------------------temperature mode 1------------------------------------------------------------------
    if [ ${@: -1} -eq 1 ]; then

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" check_field.csv)
        field_temp=$(awk '{for(i=1;i<=NF;i++)if($i == "TEMPÉRATURE(°C)")print i;}' FS=";" check_field.csv)
        cut -d";" -f$field_station,$field_date,$field_coo,$field_temp $1 >station_temp_ave0.csv

        head -1 station_temp_ave0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" >field_number.csv 

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" field_number.csv)
        field_temp=$(awk '{for(i=1;i<=NF;i++)if($i == "TEMPÉRATURE(°C)")print i;}' FS=";" field_number.csv)

        field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
        field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)
        rm field_number.csv

        tail +2 station_temp_ave0.csv | awk -v ave=$field_temp '{if($ave != "" ) print $0;}' FS=";" >station_temp_ave.csv
        rm station_temp_ave0.csv

        trait_argument_d_country $2 $3 $5 station_temp_ave.csv $field_date $field_coo
        cut -d';' -f$field_station,$field_temp cut_c.csv >station_temp_ave2.csv
        rm cut_c.csv
        if [ $4 -eq 1 ]; then
            ./exec station_temp_ave2.csv gnuplot_temp_ave.csv 3 2 1
            ./exec station_temp_ave2.csv gnuplot_temp_min.csv 2 2 1
            ./exec station_temp_ave2.csv gnuplot_temp_max.csv 1 2 1
        else
            ./exec station_temp_ave2.csv gnuplot_temp_ave.csv 3 1 1
            ./exec station_temp_ave2.csv gnuplot_temp_min.csv 2 1 1
            ./exec station_temp_ave2.csv gnuplot_temp_max.csv 1 1 1
        fi

        rm station_temp_ave2.csv

       gnuplot "t1.gnu"
        eog "t1.png" &2>/dev/null
        rm gnuplot_temp_ave.csv
        rm gnuplot_temp_min.csv
        rm gnuplot_temp_max.csv
    
    #---------------------------------------------------------------temperature mode 2------------------------------------------------------------------
    elif [ ${@: -1} -eq 2 ]; then
        field_temp=$(awk '{for(i=1;i<=NF;i++)if($i == "TEMPÉRATURE(°C)")print i;}' FS=";" check_field.csv)
        cut -d";" -f$field_date,$field_temp,$field_coo $1 >temp_date0.csv

        head -1 temp_date0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" >field_number.csv

        field_temp=$(awk '{for(i=1;i<=NF;i++)if($i == "TEMPÉRATURE(°C)")print i;}' FS=";" field_number.csv)
        field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
        field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)

        tail +2 temp_date0.csv | awk -v t=$field_temp '{if($t != "" ) print $0;}' FS=";" >temp_date.csv
        rm temp_date0.csv

        trait_argument_d_country $2 $3 $5 temp_date.csv $field_date $field_coo

        rm field_number.csv

        cut -d';' -f$field_temp,$field_date cut_c.csv >temp_date2.csv
        rm cut_c.csv

        awk '{split($1,ddate,"T") ; split(ddate[1],fdate,"-"); split(ddate[2],hdate,":"); if(hdate[1] < 10) hdate[1]=sprintf("0%d", hdate[1]);  all=sprintf("%d%s%s%s", fdate[1], fdate[2], fdate[3], hdate[1]);   print all";"$2;}' FS=";" temp_date2.csv >c_date.csv #concaténer
        rm temp_date2.csv
        if [ $4 -eq 1 ]; then
            ./exec c_date.csv gnuplot_temp_date.csv 5 2 1
        else
            ./exec c_date.csv gnuplot_temp_date.csv 5 1 1
        fi
        rm c_date.csv
        gnuplot "t2.gnu"
        eog "t2.png" &2>/dev/null
        rm gnuplot_temp_date.csv
    
    #---------------------------------------------------------------temperature mode 3------------------------------------------------------------------ 
    elif [ ${@: -1} -eq 3 ]; then

        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" check_field.csv)
        field_temp=$(awk '{for(i=1;i<=NF;i++)if($i == "TEMPÉRATURE(°C)")print i;}' FS=";" check_field.csv)

        cut -d";" -f$field_station,$field_date,$field_temp,$field_coo $1 >station_temp_date0.csv

        head -1 station_temp_date0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" >field_number.csv

        field_temp=$(awk '{for(i=1;i<=NF;i++)if($i == "TEMPÉRATURE(°C)")print i;}' FS=";" field_number.csv)
        field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
        field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)
        field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" field_number.csv)
        rm field_number.csv

        tail +2 station_temp_date0.csv | awk -v t=$field_temp '{if($t != "" ) print $0;}' FS=";" >station_temp_date.csv
        rm station_temp_date0.csv

        trait_argument_d_country $2 $3 $5 station_temp_date.csv $field_date $field_coo

        cut -d';' -f$field_temp,$field_date,$field_station cut_c.csv >station_temp_date2.csv
        rm cut_c.csv

        awk '{split($2,ddate,"T") ; split(ddate[1],fdate,"-"); split(ddate[2],hdate,":"); if(hdate[1] < 10) hdate[1]=sprintf("0%d", hdate[1]);  all=sprintf("%d%s%s%s", fdate[1], fdate[2], fdate[3], hdate[1]);   print $1";"all";"$3;}' FS=";" station_temp_date2.csv >temp_date3.csv
        rm station_temp_date2.csv
        if [ $4 -eq 1 ]; then
            ./exec temp_date3.csv gnuplot_station_temp_date.csv 6 2 1
        else
            ./exec temp_date3.csv gnuplot_station_temp_date.csv 6 1 1
        fi
        rm temp_date3.csv
           gnuplot "t3.gnu"
        eog "t3.png" &2>/dev/null
        rm gnuplot_station_temp_date.csv

    fi

}

trait_argument_d_country() {

    file=0
    if [ $1 -eq 1 ]; then

        start_b=${choice%%,*}
        finish_b=choice2=${choice#*,}
        start=$(echo $start_b | sed -e "s|/||g") #the begin of the user's choice
        finish=$(echo $finish_b | sed -e "s|/||g") #the after of the user's choice
        case $5 in

        2)
            awk -v st=$start -v fn=$finish '{split($2,ddate,"T") ; split(ddate[1],compil,"-"); all=sprintf("%d%s%s", compil[1], compil[2], compil[3]); if(all <= fn && all >= st) print $0;}' FS=";" $4 >cut_date.csv #cut les dates;
            file="cut_date.csv"
            ;;
        1)
            awk -v st=$start -v fn=$finish '{split($1,ddate,"T") ; split(ddate[1],compil,"-"); all=sprintf("%d%s%s", compil[1], compil[2], compil[3]); if(all <= fn && all >= st) print $0;}' FS=";" $4 >cut_date.csv #cut les dates
            file="cut_date.csv"
            ;;
        3)
            awk -v st=$start -v fn=$finish '{split($3,ddate,"T") ; split(ddate[1],compil,"-"); all=sprintf("%d%s%s", compil[1], compil[2], compil[3]); if(all <= fn && all >= st) print $0;}' FS=";" $4 >cut_date.csv #cut les dates
            file="cut_date.csv"
            ;;
        4)
            awk -v st=$start -v fn=$finish '{split($4,ddate,"T") ; split(ddate[1],compil,"-"); all=sprintf("%d%s%s", compil[1], compil[2], compil[3]); if(all <= fn && all >= st) print $0;}' FS=";" $4 >cut_date.csv #cut les dates
            file="cut_date.csv"
            ;;
        5)
            awk -v st=$start -v fn=$finish '{split($5,ddate,"T") ; split(ddate[1],compil,"-"); all=sprintf("%d%s%s", compil[1], compil[2], compil[3]); if(all <= fn && all >= st) print $0;}' FS=";" $4 >cut_date.csv #cut les dates
            file="cut_date.csv"
            ;;
        *)
            awk -v st=$start -v fn=$finish '{split($6,ddate,"T") ; split(ddate[1],compil,"-"); all=sprintf("%d%s%s", compil[1], compil[2], compil[3]); if(all <= fn && all >= st) print $0;}' FS=";" $4 >cut_date.csv #cut les dates
            file="cut_date.csv"
            ;;
        esac
        #allow to cut the date between the user's choices
    fi

    #if the date is not choose
    if [ "$file" = "0" ]; then

        file=$4

    fi

    case $3 in

    1)
        case $6 in

        2)
            awk '{split($2,fr,","); if(fr[1] + 0 <= 52 && fr[1] + 0 >= 40 && fr[2] + 0 >= -5 && fr[2]  + 0 <= 10) print $0;}' FS=";" $file >cut_c.csv
            ;;
        3)
            awk '{split($3,fr,","); if(fr[1] + 0 <= 52 && fr[1] + 0 >= 40 && fr[2] + 0 >= -5 && fr[2]  + 0 <= 10) print $0;}' FS=";" $file >cut_c.csv
            ;;

        4)
            awk '{split($4,fr,","); if(fr[1] + 0 <= 52 && fr[1] + 0 >= 40 && fr[2] + 0 >= -5 && fr[2]  + 0 <= 10) print $0;}' FS=";" $file >cut_c.csv
            ;;
        *)
            awk '{split($5,fr,","); if(fr[1] + 0 <= 52 && fr[1] + 0 >= 40 && fr[2] + 0 >= -5 && fr[2]  + 0 <= 10) print $0;}' FS=";" $file >cut_c.csv
            ;;
        esac
        #cut according to france
        ;;
    2)
        case $6 in

        2)
            awk '{split($2,fr,","); if(fr[1] + 0 < 6 && fr[1] + 0 > 2 && fr[2] + 0 >= -55 && fr[2] + 0 <= -50) print $0;}' FS=";" $file > cut_c.csv
            ;;
        3)
            awk '{split($3,fr,","); if(fr[1] + 0 < 6 && fr[1] + 0 > 2 && fr[2] + 0 >= -55 && fr[2] + 0 <= -50) print $0;}' FS=";" $file > cut_c.csv
            ;;
        4)
            awk '{split($4,fr,","); if(fr[1] + 0 < 6 && fr[1] + 0 > 2 && fr[2] + 0 >= -55 && fr[2] + 0 <= -50) print $0;}' FS=";" $file > cut_c.csv
            ;;
        *)
            awk '{split($5,fr,","); if(fr[1] + 0 < 6 && fr[1] + 0 > 2 && fr[2] + 0 >= -55 && fr[2] + 0 <= -50) print $0;}' FS=";" $file >cut_c.csv
            ;;
        esac

        #cut according to french guiana 
        ;;
    3)
        case $6 in

        2)
            awk '{split($2,fr,","); if(fr[1] + 0 <= 47.2 && fr[1] + 0 >= 46.5 && ft[2] + 0 >= -58 && ft[2] + 0 <= -55) print $0;}' FS=";" $file >cut_c.csv
            ;;
        3)
            awk '{split($3,fr,","); if(fr[1] + 0 <= 47.2 && fr[1] + 0 >= 46.5 && ft[2] + 0 >= -58 && ft[2] + 0 <= -55) print $0;}' FS=";" $file >cut_c.csv
            ;;
        4)
            awk '{split($4,fr,","); if(fr[1] + 0 <= 47.2 && fr[1] + 0 >= 46.5 && ft[2] + 0 >= -58 && ft[2] + 0 <= -55) print $0;}' FS=";" $file >cut_c.csv
            ;;
        *)
            awk '{split($5,fr,","); if(fr[1] + 0 <= 47.2 && fr[1] + 0 >= 46.5 && ft[2] + 0 >= -58 && ft[2] + 0 <= -55) print $0;}' FS=";" $file >cut_c.csv
            ;;
        esac

        #cut according to de Saint-Pierre et Miquelon
        ;;
    4)
        case $6 in

        2)
            awk '{split($2,fr,","); if(fr[1] + 0 <= 19 && fr[1] + 0 >= 11 && fr[2] + 0 >= -66 && fr[2] + 0 <= -58) print $0;}' FS=";" $file >cut_c.csv
            ;;
        3)
            awk '{split($3,fr,","); if(fr[1] + 0 <= 19 && fr[1] + 0 >= 11 && fr[2] + 0 >= -66 && fr[2] + 0 <= -58) print $0;}' FS=";" $file >cut_c.csv
            ;;
        4)
            awk '{split($4,fr,","); if(fr[1] + 0 <= 19 && fr[1] + 0 >= 11 && fr[2] + 0 >= -66 && fr[2] + 0 <= -58) print $0;}' FS=";" $file >cut_c.csv
            ;;
        *)
            awk '{split($5,fr,","); if(fr[1] + 0 <= 19 && fr[1] + 0 >= 11 && fr[2] + 0 >= -66 && fr[2] + 0 <= -58) print $0;}' FS=";" $file >cut_c.csv
            ;;
        esac

        #cut according to west indies
        ;;
    5)
        case $6 in

        2)
            awk '{split($2,fr,","); if(fr[1] + 0 <= -60) print $0;}' FS=";" $file >cut_c.csv
            ;;
        3)
            awk '{split($3,fr,","); if(fr[1] + 0 <= -60) print $0;}' FS=";" $file >cut_c.csv
            ;;
        4)
            awk '{split($4,fr,","); if(fr[1] + 0 <= -60) print $0;}' FS=";" $file >cut_c.csv
            ;;
        *)
            awk '{split($5,fr,","); if(fr[1] + 0 <= -60) print $0;}' FS=";" $file >cut_c.csv
            ;;
        esac

        #cut according to antarctic
        ;;
    6)
        case $6 in

        2)
            awk '{split($2,fr,",");if(fr[1] + 0 >= -55 && fr[1] + 0 <= 22 && fr[2] + 0 > 21 && fr[2] + 0 <= 132)  print $0;}' FS=";" $file >cut_c.csv
            ;;
        3)
            awk '{split($3,fr,",");if(fr[1] + 0 >= -55 && fr[1] + 0 <= 22 && fr[2] + 0 > 21 && fr[2] + 0 <= 132)  print $0;}' FS=";" $file >cut_c.csv
            ;;
        4)
            awk '{split($4,fr,",");if(fr[1] + 0 >= -55 && fr[1] + 0 <= 22 && fr[2] + 0 > 21 && fr[2] + 0 <= 132)  print $0;}' FS=";" $file >cut_c.csv
            ;;
        *)
            awk '{split($5,fr,",");if(fr[1] + 0 >= -55 && fr[1] + 0 <= 22 && fr[2] + 0 > 21 && fr[2] + 0 <= 132)  print $0;}' FS=";" $file >cut_c.csv
            ;;
        esac

        ;;
        #cut according to indian ocean

    *)
        cp $file cut_c.csv #paste the file in other
        ;;
    esac
    if [ "$file" != "$4" ]; then
        rm $file
        rm $4
    else
        rm $4

    fi

}

check_argument() {
    #initialize the variables
    d=0
    x=0
    choice1=0
    choice2=0
    count=0
    after=0
    check=0
    h=0
    t=0
    p=0
    w=0
    m=0
    sort=1
    r=0
    allchoice=0
    #check the -f and the input file
    for k in $@; do

        if [ $after -eq 1 ]; then
            if file_check $k; then

                head -1 $k | sed 's/.*/\U&/' | sed -e "s/ //g" >check_field.csv

                file=$k
                check=1
                break
            else
                echo " the file is not good "
                exit 1
            fi

        fi

        if [ "$k" = "-f" ]; then
            after=1

        fi
    done
    #check if the argument f exist
    if [ $check -ne 1 ]; then
        echo "you forgot the option -f or the file is not good"
        exit 1
    fi
    #check if the field station exist
    if [ ! $(grep IDOMMSTATION check_field.csv) ]; then
        echo "the field station don't exist"
        exit 1
    fi
    if [ ! $(grep COORDONNEES check_field.csv) ]; then
        echo "the field coordonnees don't exist"
        exit 1
    fi
    #check the arguments command
    while getopts "t:p:wmhf:rFGSAOQd:-:" option; do

        case $option in
        #file
        f) ;;

        #height
        h)
            if [ ! $(grep ALTITUDE check_field.csv) ]; then
                echo "the field altitude don't exist"
                h=0
            else
                h=1
                count=$(($count + 1)) #allow to count the number of option
            fi

            ;;
        #moisture
        m)
            if [ ! $(grep HUMIDITÉ check_field.csv) ]; then
                echo "the field humidité don't exist"
                m=0
            else
                m=1
                count=$(($count + 1))
            fi

            ;;
        #wind
        w)
            if [ ! $(grep DIRECTIONDUVENTMOYEN10MN check_field.csv) ] || [ ! $(grep VITESSEDUVENTMOYEN10MN check_field.csv) ]; then
                echo "the field direction du vent moyen 10 mn or vitesse du vent moyen 10 mn don't exist"
                w=0
            else
                w=1
                count=$(($count + 1))
            fi
            ;;
        #pressure
        p)
            if [ "$OPTARG" != "1" ] && [ "$OPTARG" != "2" ] && [ "$OPTARG" != "3" ]; then
                echo "p option argument must be 1 2 or 3"
                exit 1
            fi

            if [ ! $(grep PRESSIONSTATION check_field.csv) ]; then
                echo "the field pression station don't exist"
                p=0 #choisir les champs
            elif [ "$OPTARG" = "1" ]; then
                if [ $p -ne 0 ]; then 
                    echo "you can choose only one pressure option"
                    exit 4
                fi
                p=1
                count=$(($count + 1))
            elif [ "$OPTARG" = "2" ]; then
                if [ $p -ne 0 ]; then 
                    echo "you can choose only one pressure option"
                    exit 4
                fi
                p=2
                count=$(($count + 1))
            else
                if [ $p -ne 0 ]; then 
                    echo "you can choose only one pressure option"
                    exit 4
                fi
                count=$(($count + 1))
                p=3
            fi
            ;;
        #temperature
        t)
            if [ "$OPTARG" != "1" ] && [ "$OPTARG" != "2" ] && [ "$OPTARG" != "3" ]; then
                echo "t option argument must be 1 2 or 3"
                exit 1
            fi
            if [ ! $(grep "TEMPÉRATURE(°C)" check_field.csv) ] || [ ! $(grep "TEMPÉRATUREMINIMALESUR24HEURES(°C)" check_field.csv) ] || [ ! $(grep "TEMPÉRATUREMAXIMALESUR24HEURES(°C)" check_field.csv) ]; then
                echo "the field température (°C), température minimale sur 24 heures (°C) or température minimale sur 24 heures (°C) don't exist"
                t=0 #choisir les champs
            elif [ "$OPTARG" = "1" ]; then
                if [ $t -ne 0 ]; then 
                    echo "you can choose only one temperature option"
                    exit 4
                fi
                t=1
                count=$(($count + 1))
            elif [ "$OPTARG" = "2" ]; then
                if [ $t -ne 0 ]; then 
                    echo "you can choose only one temperature option"
                    exit 4
                fi
                t=2
                count=$(($count + 1))
            else
                if [ $t -ne 0 ]; then 
                    echo "you can choose only one temperature option"
                    exit 4
                fi
                count=$(($count + 1))
                t=3
            fi
            ;;
        r) 
            r=1
        ;;
        -)
            case $OPTARG in
            avl)
                if [ $sort -ne 1 ]; then
                    echo "you can choose only one method of sort"
                    exit 1
                fi
                sort=1 #avl verif qu il en a pas mis 2 et l envoyer apres au programme
                ;;
            abr)
                if [ $sort -ne 1 ]; then
                    echo "you can choose only one method of sort"
                    exit 1
                fi
                sort=2 #abr
                ;;
            tab)
                if [ $sort -ne 1 ]; then
                    echo "you can choose only one method of sort"
                    exit 1
                fi
                sort=3 #list
                ;;
            help)
                cat README.md #help
                ;;
            *)
                echo "-- option argument must be avl, abr, help or tab"
                exit 1
                ;;
            esac
            ;;

        F)
            if [ $x -ne 0 ]; then
                echo "you need to choose only one location"
                exit 1
            fi

            x=1
            ;;
        G)
            if [ $x -ne 0 ]; then
                echo "you need to choose only one location"
                exit 1
            fi
            x=2

            ;;
        S)
            if [ $x -ne 0 ]; then
                echo "you need to choose only one location"
                exit 1
            fi
            x=3
            ;;
        A)
            if [ $x -ne 0 ]; then
                echo "you need to choose only one location"
                exit 1
            fi
            x=4

            ;;

        Q)
            if [ $x -ne 0 ]; then
                echo "you need to choose only one location"
                exit 1
            fi
            x=5
            ;;
        O)
            if [ $x -ne 0 ]; then
                echo "you need to choose only one location"
                exit 1
            fi
            x=6
            ;;
        d)
            begin=$(date -d "2010/01/01" +%s)
            finish=$(date -d "2022/12/30" +%s)
            choice=$OPTARG
            choice1=${choice%%,*}
            choice2=${choice#*,}

            if [ ! $(date -d "$choice1" +%s) ] || [ ! $(date -d "$choice2" +%s) ]; then
                exit 1
            fi
            choice1=$(date -d "$choice1" +%s)
            choice2=$(date -d "$choice2" +%s)

            if [ $choice1 -gt $choice2 ] || [ $choice1 -lt $begin ] || [ $choice1 -gt $finish ] || [ $choice2 -lt $begin ] || [ $choice2 -gt $finish ]; then
                echo " you can't choose a date before the 2010/01/01 and after the 2021/12/31 and the first date must be the smallest"
            fi
            d=1
            choice1=${choice%%,*}
            choice2=${choice#*,}
            allchoice=$(echo "$choice1,$choice1")
            ;;
        *) ;;

        esac
    done
    #check if the user have choose at least one option
    if [ $count -eq 0 ]; then
        echo "you must choose an option"
    fi
    #check if the user do the good option with the good sort
    re=0
    if [ $sort -eq 3 ]; then

        if [ $r -eq 1 ]; then
            echo "you can't reverse with tab"
            exit 2

        elif [ $p -ne 0 ] && [ $p -ne 1 ]; then
               
            echo "you can't do your sort with the tab but you can choose 2 for abr or 1 for avl"
            read re

            while [ "$re" != "1" ] && [ "$re" != "2" ];do
                echo "choose 1 for avl and 2 for abr"
            done
            sort=$re         

        elif [ $t -ne 0 ] && [ $t -ne 1 ]; then
                 
            echo "you can't do your sort with the tab but you can choose 2 for abr or 1 for avl"
            read re

            while [ "$re" != "1" ] && [ "$re" != "2" ];do
                echo "choose 1 for avl and 2 for abr"
            done
            sort=$re
            
        else
            trait_argument_tab $file $d $allchoice $r $x $h $m $w $p $t
        fi
    fi

    if [ $sort -eq 2 ]; then
        trait_argument_abr $file $d $allchoice $r $x $h $m $w $p $t
    elif [ $sort -eq 1 ]; then 
        trait_argument_avl $file $d $allchoice $r $x $h $m $w $p $t
    fi

}

make -f Makefile.mak
check_argument $@
rm check_field.csv

