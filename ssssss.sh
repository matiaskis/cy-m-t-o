
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
trait_argument_avl() {     

field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" check_field.csv)
field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" check_field.csv)


 if [ $6 -eq 1 ]; then   

    field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" check_field.csv)
    field_height=$(awk '{for(i=1;i<=NF;i++)if($i == "ALTITUDE")print i;}' FS=";" check_field.csv)

    
    cut -d';' -f$field_station,$field_date,$field_coo,$field_height $1 > station_height0.csv   
   
    head -1 station_height0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" > field_number.csv #avoir l'entete des 4 colonnes
    field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" field_number.csv)
    field_height=$(awk '{for(i=1;i<=NF;i++)if($i == "ALTITUDE")print i;}' FS=";" field_number.csv)
    field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
    field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)
    rm field_number.csv

    tail +2 station_height0.csv  | awk -v h=$field_height '{if($h != "" ) print $0;}' FS=";" > station_height.csv #enlever espace
    rm station_height0.csv
    trait_argument_d_country $2 $3 $4 $5 station_height.csv $field_date $field_coo       

    cut -d';' -f$field_station,$field_height cut_c.csv > station_height2.csv  
    
    
    #rm cut_c.csv
    ./exec station_height2.csv gnuplot_height.csv 4 2
    #rm station_height2.csv
   
    #fini sauf gnuplot
fi

if [ $7 -eq 1 ]; then

    field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" check_field.csv)
    field_moisture=$(awk '{for(i=1;i<=NF;i++)if($i == "HUMIDITÉ")print i;}' FS=";" check_field.csv)
    cut -d';' -f$field_station,$field_date,$field_moisture,$field_coo $1  > station_m0.csv

    head -1 station_m0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" > field_number.csv #avoir l'entete des 4 colonnes
    
    field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" field_number.csv)
    field_moisture=$(awk '{for(i=1;i<=NF;i++)if($i == "HUMIDITÉ")print i;}' FS=";" field_number.csv)    
    field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
    field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)
    rm field_number.csv

    tail +2 station_m0.csv | awk -v m=$field_moisture '{if($m != "" ) print $0;}' FS=";"  > station_m.csv
    rm station_m0.csv
    trait_argument_d_country $2 $3 $4 $5 station_m.csv $field_date $field_coo
    
    cut -d';' -f$field_station,$field_moisture cut_c.csv > station_m2.csv 
    
    rm cut_c.csv
    ./exec station_m2.csv station_m.csv 7 2 1
    rm station_m2.csv
    
    ./exec station_m.csv gnuplot_m.csv 7 2 0
    
    rm station_m.csv

    #manque gnuplot
    
fi
if [ $8 -eq 1 ]; then

    field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" check_field.csv)
    field_wind1=$(awk '{for(i=1;i<=NF;i++)if($i == "DIRECTIONDUVENTMOYEN10MN")print i;}' FS=";" check_field.csv)
    field_wind2=$(awk '{for(i=1;i<=NF;i++)if($i == "VITESSEDUVENTMOYEN10MN")print i;}' FS=";" check_field.csv)
    cut -d';' -f$field_station,$field_date,$field_wind1,$field_wind2,$field_coo $1 > station_wind0.csv
    
    head -1 station_wind0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" > field_number.csv #avoir l'entete des 4 colonnes
    
    field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" field_number.csv)
    field_wind1=$(awk '{for(i=1;i<=NF;i++)if($i == "DIRECTIONDUVENTMOYEN10MN")print i;}' FS=";" field_number.csv)
    field_wind2=$(awk '{for(i=1;i<=NF;i++)if($i == "VITESSEDUVENTMOYEN10MN")print i;}' FS=";" field_number.csv)
    field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
    field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)
    rm field_number.csv

    tail +2 station_wind0.csv |  awk -v w=$field_wind1 -v w2=$field_wind2 '{if($w != "" && $w2 != "" )  print $0;}' FS=";" > station_wind.csv
    rm station_wind0.csv
    trait_argument_d_country $2 $3 $4 $5 station_wind.csv $field_date $field_coo

    cut -d';' -f$field_station,$field_wind1,$field_wind2 cut_c.csv > station_wind2.csv 
    
    rm cut_c.csv
    ./exec station_wind2.csv gnuplot_wind.csv 8 1 
    rm station_wind2.csv
    #amner longitude et lattitude
    #gnuplot
fi

if [ $9 -eq 1 ]; then

    field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" check_field.csv)
    field_pressure=$(awk '{for(i=1;i<=NF;i++)if($i == "PRESSIONSTATION")print i;}' FS=";" check_field.csv)

    cut -d";" -f$field_station,$field_date,$field_pressure,$field_coo $1 > station_pres_ave0.csv

    head -1 station_pres_ave0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" > field_number.csv #avoir l'entete des 4 colonnes
    
    field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" field_number.csv)
    field_pressure=$(awk '{for(i=1;i<=NF;i++)if($i == "PRESSIONSTATION")print i;}' FS=";" field_number.csv)
    field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
    field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)
    rm field_number.csv

    tail +2 station_pres_ave0.csv | awk -v ave=$field_pressure '{if($ave != "" ) print $0;}' FS=";" > station_pres_ave.csv
    rm station_pres_ave0.csv
    trait_argument_d_country $2 $3 $4 $5 station_pres_ave.csv $field_date $field_coo   
    
    cut -d';' -f$field_station,$field_pressure cut_c.csv > station_pres_ave2.csv

    rm cut_c.csv
    ./exec station_pres_ave2.csv gnuplot_pres_ave.csv 3 1
    ./exec station_pres_ave2.csv gnuplot_pres_min.csv 2 1
    ./exec station_pres_ave2.csv gnuplot_pres_max.csv 1 1
    rm station_pres_ave2.csv;

    #fini sauf gnuplot
elif [ $9 -eq 2 ]; then
    field_pressure=$(awk '{for(i=1;i<=NF;i++)if($i == "PRESSIONSTATION")print i;}' FS=";" check_field.csv)


    cut -d";" -f$field_date,$field_pressure,$field_coo $1 > pres_date0.csv

    head -1 pres_date0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" > field_number.csv #avoir l'entete des 3 colonnes
    
    field_pressure=$(awk '{for(i=1;i<=NF;i++)if($i == "PRESSIONSTATION")print i;}' FS=";" field_number.csv)
    field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
    field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)
    

    tail +2 pres_date0.csv | awk -v p=$field_pressure '{if($p != "" ) print $0;}' FS=";" > pres_date.csv
    rm pres_date0.csv

    trait_argument_d_country $2 $3 $4 $5 pres_date.csv $field_date $field_coo

    
    rm field_number.csv

    cut -d';' -f$field_pressure,$field_date cut_c.csv > pres_date2.csv
    rm cut_c.csv
    

    awk '{split($1,ddate,"T") ; split(ddate[1],fdate,"-"); split(ddate[2],hdate,":"); if(hdate[1] < 10) hdate[1]=sprintf("0%d", hdate[1]);  all=sprintf("%d%s%s%s", fdate[1], fdate[2], fdate[3], hdate[1]);   print all";"$2;}' FS=";" pres_date2.csv > c_date.csv #cut les dates 
    rm pres_date2.csv;
   
    ./exec c_date.csv gnuplot_pres_date.csv 5 1
    rm c_date.csv;

    #gnuplot
elif [ $9 -eq 3 ]; then

    field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" check_field.csv)
    field_pressure=$(awk '{for(i=1;i<=NF;i++)if($i == "PRESSIONSTATION")print i;}' FS=";" check_field.csv)

    cut -d";" -f$field_station,$field_date,$field_pressure,$field_coo  $1 > station_pres_date0.csv
    
    head -1 station_pres_date0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" > field_number.csv 
    
    field_pressure=$(awk '{for(i=1;i<=NF;i++)if($i == "PRESSIONSTATION")print i;}' FS=";" field_number.csv)
    field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
    field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)
    field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" field_number.csv)
    rm field_number.csv
    
    
    tail +2 station_pres_date0.csv | awk -v p=$field_pressure '{if($p != "" ) print $0;}' FS=";"  > station_pres_date.csv
    rm station_pres_date0.csv

    trait_argument_d_country $2 $3 $4 $5 station_pres_date.csv $field_date $field_coo
    
   
    

    cut -d';' -f$field_pressure,$field_date,$field_station cut_c.csv > station_pres_date2.csv
    rm cut_c.csv
    

    awk '{split($2,ddate,"T") ; split(ddate[1],fdate,"-"); split(ddate[2],hdate,":"); if(hdate[1] < 10) hdate[1]=sprintf("0%d", hdate[1]);  all=sprintf("%d%s%s%s", fdate[1], fdate[2], fdate[3], hdate[1]);   print $1";"all";"$3;}' FS=";" station_pres_date2.csv > pres_date3.csv

    rm station_pres_date2.csv

    ./exec pres_date3.csv gnuplot_station_pres_date.csv 6 1
    rm pres_date3.csv;
    #gnuplot
fi  

if [ ${@: -1} -eq 1 ]; then

    field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" check_field.csv)
    field_temp=$(awk '{for(i=1;i<=NF;i++)if($i == "TEMPÉRATURE(°C)")print i;}' FS=";" check_field.csv)
    cut -d";" -f$field_station,$field_date,$field_coo,$field_temp $1 > station_temp_ave0.csv

    head -1 station_temp_ave0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" > field_number.csv #avoir l'entete des 4 colonnes
    
    field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" field_number.csv)
    field_temp=$(awk '{for(i=1;i<=NF;i++)if($i == "TEMPÉRATURE(°C)")print i;}' FS=";" field_number.csv)
    
    field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
    field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)
    rm field_number.csv

    tail +2 station_temp_ave0.csv | awk -v ave=$field_temp '{if($ave != "" ) print $0;}' FS=";" > station_temp_ave.csv
    rm station_temp_ave0.csv
    
    trait_argument_d_country $2 $3 $4 $5 station_temp_ave.csv $field_date $field_coo   
    cut -d';' -f$field_station,$field_temp cut_c.csv > station_temp_ave2.csv
    rm cut_c.csv   

    ./exec station_temp_ave2.csv gnuplot_temp_ave.csv 3 1
    ./exec station_temp_ave2.csv gnuplot_temp_min.csv 2 1
    ./exec station_temp_ave2.csv gnuplot_temp_max.csv 1 1

    rm station_temp_ave2.csv;

    #gnuplot pression_moyenne.sh
    
    #fini sauf gnuplot
elif [ ${@: -1} -eq 2 ]; then
    field_temp=$(awk '{for(i=1;i<=NF;i++)if($i == "TEMPÉRATURE(°C)")print i;}' FS=";" check_field.csv)
    cut -d";" -f$field_date,$field_temp,$field_coo $1 > temp_date0.csv

    head -1 temp_date0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" > field_number.csv #avoir l'entete des 3 colonnes
    
    field_temp=$(awk '{for(i=1;i<=NF;i++)if($i == "TEMPÉRATURE(°C)")print i;}' FS=";" field_number.csv)
    field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
    field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)
    

    tail +2 temp_date0.csv | awk -v t=$field_temp '{if($p != "" ) print $0;}' FS=";" > temp_date.csv
    rm temp_date0.csv

    trait_argument_d_country $2 $3 $4 $5 temp_date.csv $field_date $field_coo

    rm field_number.csv

    cut -d';' -f$field_temp,$field_date cut_c.csv > temp_date2.csv
    rm cut_c.csv
    

    awk '{split($1,ddate,"T") ; split(ddate[1],fdate,"-"); split(ddate[2],hdate,":"); if(hdate[1] < 10) hdate[1]=sprintf("0%d", hdate[1]);  all=sprintf("%d%s%s%s", fdate[1], fdate[2], fdate[3], hdate[1]);   print all";"$2;}' FS=";" temp_date2.csv > c_date.csv #concaténer
    rm temp_date2.csv;
   
    ./exec c_date.csv gnuplot_temp_date.csv 5 1
    rm c_date.csv;
    #gnuplot
elif [ ${@: -1} -eq 3 ]; then

    field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" check_field.csv)
    field_temp=$(awk '{for(i=1;i<=NF;i++)if($i == "TEMPÉRATURE(°C)")print i;}' FS=";" check_field.csv)

    cut -d";" -f$field_station,$field_date,$field_temp,$field_coo $1 > station_temp_date0.csv
    
    head -1 station_temp_date0.csv | sed 's/.*/\U&/' | sed -e "s/ //g" > field_number.csv 
    
    field_temp=$(awk '{for(i=1;i<=NF;i++)if($i == "TEMPÉRATURE(°C)")print i;}' FS=";" field_number.csv)
    field_date=$(awk '{for(i=1;i<=NF;i++)if($i == "DATE")print i;}' FS=";" field_number.csv)
    field_coo=$(awk '{for(i=1;i<=NF;i++)if($i == "COORDONNEES")print i;}' FS=";" field_number.csv)
    field_station=$(awk '{for(i=1;i<=NF;i++)if($i == "IDOMMSTATION")print i;}' FS=";" field_number.csv)
    rm field_number.csv
    
    
    tail +2 station_temp_date0.csv | awk -v p=$field_temp '{if($p != "" ) print $0;}' FS=";" > station_temp_date.csv
    rm station_temp_date0.csv

    trait_argument_d_country $2 $3 $4 $5 station_temp_date.csv $field_date $field_coo
    

   

    cut -d';' -f$field_temp,$field_date,$field_station cut_c.csv > station_temp_date2.csv
    rm cut_c.csv
    

    awk '{split($2,ddate,"T") ; split(ddate[1],fdate,"-"); split(ddate[2],hdate,":"); if(hdate[1] < 10) hdate[1]=sprintf("0%d", hdate[1]);  all=sprintf("%d%s%s%s", fdate[1], fdate[2], fdate[3], hdate[1]);   print $1";"all";"$3;}' FS=";" station_temp_date2.csv > temp_date3.csv
    rm station_temp_date2.csv

    ./exec temp_date3.csv gnuplot_station_temp_date.csv 6 1
    rm temp_date3.csv;
    #gnuplot

fi 


}

trait_argument_d_country() {
    
    file=0
    if [ $1 -eq 1 ]; then
        start=$(echo $2 | sed -e "s|/||g")
        finish=$(echo $3 | sed -e "s|/||g")
        case $6 in

            2)        
                awk -v st=$start -v fn=$finish '{split($2,ddate,"T") ; split(ddate[1],compil,"-"); all=sprintf("%d%s%s", compil[1], compil[2], compil[3]); if(all <= fn && all >= st) print $0;}' FS=";" $5 > cut_date.csv #cut les dates;
                file="cut_date.csv"
            ;;
            1)  
                awk -v st=$start -v fn=$finish '{split($1,ddate,"T") ; split(ddate[1],compil,"-"); all=sprintf("%d%s%s", compil[1], compil[2], compil[3]); if(all <= fn && all >= st) print $0;}' FS=";" $5 > cut_date.csv #cut les dates 
                file="cut_date.csv"
            ;;
            3)
                 awk -v st=$start -v fn=$finish '{split($3,ddate,"T") ; split(ddate[1],compil,"-"); all=sprintf("%d%s%s", compil[1], compil[2], compil[3]); if(all <= fn && all >= st) print $0;}' FS=";" $5 > cut_date.csv #cut les dates 
                file="cut_date.csv"
            ;;
            4)  
                 awk -v st=$start -v fn=$finish '{split($4,ddate,"T") ; split(ddate[1],compil,"-"); all=sprintf("%d%s%s", compil[1], compil[2], compil[3]); if(all <= fn && all >= st) print $0;}' FS=";" $5 > cut_date.csv #cut les dates 
                file="cut_date.csv"
            ;;
            5)
                 awk -v st=$start -v fn=$finish '{split($5,ddate,"T") ; split(ddate[1],compil,"-"); all=sprintf("%d%s%s", compil[1], compil[2], compil[3]); if(all <= fn && all >= st) print $0;}' FS=";" $5 > cut_date.csv #cut les dates 
                file="cut_date.csv"
            ;; 
            *)
                awk -v st=$start -v fn=$finish '{split($6,ddate,"T") ; split(ddate[1],compil,"-"); all=sprintf("%d%s%s", compil[1], compil[2], compil[3]); if(all <= fn && all >= st) print $0;}' FS=";" $5 > cut_date.csv #cut les dates 
                file="cut_date.csv"
            ;;  
        esac
    fi
    if [ "$file" = "0" ]; then
        
        file="$5"
        
        
    fi
    case $4 in 

        1) case $7 in

                2)
                    awk '{split($2,fr,","); if(fr[1] < 51.2 && fr[1] > 41.3 && fr[2] > -5 && fr[2] < 9.7) print $0;}' FS=";" $file > cut_c.csv
                ;;
                3)
                     awk '{split($3,fr,","); if(fr[1] < 51.2 && fr[1] > 41.3 && fr[2] > -5 && fr[2] < 9.7) print $0;}' FS=";" $file > cut_c.csv
                ;;
                4)
                     awk '{split($4,fr,","); if(fr[1] < 51.2 && fr[1] > 41.3 && fr[2] > -5 && fr[2] < 9.7) print $0;}' FS=";" $file > cut_c.csv
                ;;
                *)
                     awk '{split($5,fr,","); if(fr[1] < 51.2 && fr[1] > 41.3 && fr[2] > -5 && fr[2] < 9.7) print $0;}' FS=";" $file > cut_c.csv
                ;;
            esac
            #cut en fonction de fr
        ;;
        2) case $7 in

                2)
                    awk '{split($2,fr,","); if(fr[1] < 6 && fr[1] > 2 ){ split(fr[2],ft,"-"); if(ft[2] < 55 && ft[2] > 50) print $0;}}' FS=";" $file > cut_c.csv
                ;;
                3)
                     awk '{split($3,fr,","); if(fr[1] < 6 && fr[1] > 2 ){ split(fr[2],ft,"-"); if(ft[2] < 55 && ft[2] > 50) print $0;}}' FS=";" $file > cut_c.csv
                ;;
                4)
                     awk '{split($4,fr,","); if(fr[1] < 6 && fr[1] > 2 ){ split(fr[2],ft,"-"); if(ft[2] < 55 && ft[2] > 50) print $0;}}' FS=";" $file > cut_c.csv
                ;;
                *)
                     awk '{split($5,fr,","); if(fr[1] < 6 && fr[1] > 2 ){ split(fr[2],ft,"-"); if(ft[2] < 55 && ft[2] > 50) print $0;}}' FS=";" $file > cut_c.csv
                ;;
            esac 
        
            #cut en fonction guyanne fr
        ;;
        3) case $7 in

                2)
                    awk '{split($2,fr,","); if(fr[1] < 47.2 && fr[1] > 46.5 ){ split(fr[2],ft,"-"); if(ft[2] < 57 && ft[2] > 56) print $0;}}' FS=";" $file > cut_c.csv
                ;;
                3)
                     awk '{split($3,fr,","); if(fr[1] < 47.2 && fr[1] > 46.5 ){ split(fr[2],ft,"-"); if(ft[2] < 57 && ft[2] > 56) print $0;}}' FS=";" $file > cut_c.csv
                ;;
                4)
                     awk '{split($4,fr,","); if(fr[1] < 47.2 && fr[1] > 46.5 ){ split(fr[2],ft,"-"); if(ft[2] < 57 && ft[2] > 56) print $0;}}' FS=";" $file > cut_c.csv
                ;;
                *)
                    awk '{split($5,fr,","); if(fr[1] < 47.2 && fr[1] > 46.5 ){ split(fr[2],ft,"-"); if(ft[2] < 57 && ft[2] > 56) print $0;}}' FS=";" $file > cut_c.csv
                ;;
            esac 
                       
            #cut en fonction de Saint-Pierre et Miquelon
        ;;
        4) case $7 in

                2)
                    awk '{split($2,fr,","); if(fr[1] < 19 && fr[1] > 11 ){ split(fr[2],ft,"-"); if(ft[2] < 66 && ft[2] > 58) print $0;}}' FS=";" $file > cut_c.csv
                ;;
                3)
                     awk '{split($3,fr,","); if(fr[1] < 19 && fr[1] > 11 ){ split(fr[2],ft,"-"); if(ft[2] < 66 && ft[2] > 58) print $0;}}' FS=";" $file > cut_c.csv
                ;;
                4)  
                     awk '{split($4,fr,","); if(fr[1] < 19 && fr[1] > 11 ){ split(fr[2],ft,"-"); if(ft[2] < 66 && ft[2] > 58) print $0;}}' FS=";" $file > cut_c.csv
                ;;
                *)
                     awk '{split($5,fr,","); if(fr[1] < 19 && fr[1] > 11 ){ split(fr[2],ft,"-"); if(ft[2] < 66 && ft[2] > 58) print $0;}}' FS=";" $file > cut_c.csv
                ;;
            esac 
            
            #cut antilles
        ;;
        5)
            case $7 in

                2)
                    awk '{split($10,fr,","); if(fr[1] < -60) print $0;}' FS=";" $file > cut_c.csv
                ;;
                3)
                    awk '{split($10,fr,","); if(fr[1] < -60) print $0;}' FS=";" $file > cut_c.csv
                ;;
                4)  
                    awk '{split($10,fr,","); if(fr[1] < -60) print $0;}' FS=";" $file > cut_c.csv
                ;;
                *)
                    awk '{split($10,fr,","); if(fr[1] < -60) print $0;}' FS=";" $file > cut_c.csv
                ;;
            esac 
            
            #cut antarctique mais pas fini ask to ptrofesor
        ;;
        6) case $7 in

                2)
                    awk '{split($10,fr,","); if(fr[1] < 6 && fr[1] > 2){ split(fr[2],ft,"-");  if(fr[2] < 57 && fr[2] > 50) print $0;}}' FS=";" $file > cut_c.csv
                ;;
                3)
                     awk '{split($10,fr,","); if(fr[1] < 6 && fr[1] > 2){ split(fr[2],ft,"-");  if(fr[2] < 57 && fr[2] > 50) print $0;}}' FS=";" $file > cut_c.csv
                ;;
                4)  
                     awk '{split($10,fr,","); if(fr[1] < 6 && fr[1] > 2){ split(fr[2],ft,"-");  if(fr[2] < 57 && fr[2] > 50) print $0;}}' FS=";" $file > cut_c.csv
                ;;
                *)
                    awk '{split($10,fr,","); if(fr[1] < 6 && fr[1] > 2){ split(fr[2],ft,"-");  if(fr[2] < 57 && fr[2] > 50) print $0;}}' FS=";" $file > cut_c.csv
                ;;
            esac 
            
        
        ;;
        *)
            cp $file cut_c.csv
        ;;
    esac
    if [ "$file" != "$5" ]; then
        rm $file
        rm $5;
    else
        rm $5
       
    fi


}



check_argument(){   
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
    tri=0
    for k in $@; do

        if [ $after -eq 1 ]; then 
            if file_check $k; then
                
             head -1 $k | sed 's/.*/\U&/' | sed -e "s/ //g" > check_field.csv 
             
             file=$k
             check=1
             break;
            else
             echo " the file is not good "
             exit 1
            fi

        fi

        if [ "$k" = "-f" ]; then
            after=1
            
        fi
    done

    if [ $check -ne 1 ]; then
        echo "you forgot the option -f or the file is not good"
        exit 1
    fi
    if [ ! $(grep IDOMMSTATION check_field.csv) ]; then
        echo "the field station don't exist"
        exit 1
    fi
     if [ ! $(grep COORDONNEES check_field.csv) ]; then
        echo "the field coordonnees don't exist"
        exit 1
    fi
 
     while getopts "t:p:wmhf:FGSAOQd:-:" option
       do
               
               case $option in
                    #file
                    f)  
                    ;;
                    #height
                    h) if [ ! $(grep ALTITUDE check_field.csv) ]; then
                            echo "the field altitude don't exist"
                            h=0;
                        else
                            h=1
                            count=$(($count+1)); #permet de vérifier à la fin que au moins un tris est possible
                        fi
                        
                    ;;
                    #moisture
                    m) if [ ! $(grep HUMIDITÉ check_field.csv) ]; then
                            echo "the field humidité don't exist"
                            m=0;
                        else
                            m=1
                            count=$(($count+1));
                        fi
                        
                    ;;
                    #wind
                    w) if [ ! $(grep DIRECTIONDUVENTMOYEN10MN check_field.csv) ] || [ ! $(grep  VITESSEDUVENTMOYEN10MN check_field.csv) ] ; then
                            echo "the field direction du vent moyen 10 mn or vitesse du vent moyen 10 mn don't exist"
                            w=0;
                        else
                            w=1
                            count=$(($count+1));
                        fi
                    ;;
                    #pressure
                    p) if [ "$OPTARG" != "1" ] && [ "$OPTARG" != "2" ] && [ "$OPTARG" != "3"  ]; then
                            echo"p option argument must be 1 2 or 3"
                            exit 1
                        fi
                        
                        if [ ! $(grep PRESSIONSTATION check_field.csv ) ]; then
                            echo "the field pression station don't exist"
                            p=0; #choisir les champs 
                        elif [ "$OPTARG" = "1" ]; then
                            p=1
                            count=$(($count+1));
                        elif [ "$OPTARG" = "2" ]; then
                            p=2           
                            count=$(($count+1));             
                        else 
                            count=$(($count+1))
                            p=3;                        
                        fi
                    ;;
                    #temperature
                    t) if [ "$OPTARG" != "1" ] && [ "$OPTARG" != "2" ] && [ "$OPTARG" != "3"  ]; then
                            echo"t option argument must be 1 2 or 3"
                            exit 1
                        fi
                       if [ ! $(grep  "TEMPÉRATURE(°C)" check_field.csv ) ] || [ ! $(grep  "TEMPÉRATUREMINIMALESUR24HEURES(°C)" check_field.csv ) ] || [ ! $(grep  "TEMPÉRATUREMAXIMALESUR24HEURES(°C)" check_field.csv ) ]; then
                            echo "the field température (°C), température minimale sur 24 heures (°C) or température minimale sur 24 heures (°C) don't exist"
                            t=0; #choisir les champs 
                        elif [ "$OPTARG" = "1" ]; then
                            t=1
                            count=$(($count+1));
                        elif [ "$OPTARG" = "2" ]; then
                            t=2           
                            count=$(($count+1));             
                        else 
                            count=$(($count+1))
                            t=3;                        
                        fi
                    ;;
                    -) case $OPTARG in 
                          avl) 
                            if [ $tri -ne 0 ]; then
                                echo "you can choose only one method of sort"
                                exit 1
                            fi
                            tri=1 #avl verif qu il en a pas mis 2 et l envoyer apres au programme
                            ;;
                            abr)
                                if [ $tri -ne 0 ]; then
                                    echo "you can choose only one method of sort"
                                    exit 1
                                fi 
                                tri=2 #abr
                           ;;
                            tab) 
                                if [ $tri -ne 0 ]; then
                                    echo "you can choose only one method of sort"
                                    exit 1
                                fi
                                tri=3 #list
                            ;;
                           help) help=1 #help
                            ;;
                            *) echo"-- option argument must be avl, abr, help or tab"
                            exit 1
                            ;;
                        esac
                    ;;

                    F) if [ $x -ne 0 ]; then
                            echo "you need to choose only one location"
                            exit 1
                        fi
                        
                            x=1                      
                    ;;
                    G)  if [ $x -ne 0 ]; then
                            echo "you need to choose only one location"
                            exit 1
                        fi
                            x=2
                        
                    ;;
                    S)  if [ $x -ne 0 ]; then
                            echo "you need to choose only one location"
                            exit 1
                        fi                      
                            x=3                       
                    ;;
                    A)  if [ $x -ne 0 ]; then
                            echo "you need to choose only one location"
                            exit 1
                        fi                     
                            x=4
                        
                    ;;

                    Q)  if [ $x -ne 0 ]; then
                            echo "you need to choose only one location"
                            exit 1
                        fi
                            x=5
                    ;;
                    O)  if [ $x -ne 0 ]; then
                            echo "you need to choose only one location"
                            exit 1
                        fi
                            x=6
                    ;;
                    d)                      
                            begin=$(date -d "2010/01/01" +%s)
                            finish=$(date -d "2021/12/31" +%s)
                            choice=$OPTARG
                            choice1=${choice%%,*}
                            choice2=${choice#*,}
                       
                            if [ ! $(date -d "$choice1" +%s) ] || [ ! $(date -d "$choice2" +%s) ]; then
                                exit 1
                            fi
                            choice1=$(date -d "$choice1" +%s)
                            choice2=$(date -d "$choice2" +%s)
                          
                            if [ $choice1 -gt $choice2 ] || [ $choice1 -lt $begin ] || [ $choice1 -gt $finish ] || [ $choice2 -lt $begin ] || [ $choice2 -gt $finish  ]; then
                                echo " you can't choose a date before the 2010/01/01 and after the 2021/12/31 and the first date must be the smallest"
                            fi 
                            d=1
                            choice1=${choice%%,*}
                            choice2=${choice#*,}                       
                        ;;
                        *) 
                        ;;
                esac
            done
            if [ $count -eq 0 ]; then
                echo "you must choose an option"
            fi
                
            if [ $tri -eq 3 ]; then
                trait_argument_tab $file $d $choice1 $choice2 $x $h $m $w $p $t;
            elif [ $tri -eq 2 ]; then
                trait_argument_abr $file $d $choice1 $choice2 $x $h $m $w $p $t;
            else 
                trait_argument_avl $file $d $choice1 $choice2 $x $h $m $w $p $t;
            fi
    
    
            
}

make -f Makefile.mak
check_argument $@

