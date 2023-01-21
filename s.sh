
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
trait_argument() {     
 if [ "$6" = "1" ]; then   
  
    tail +2 $1 | cut -d';' -f1,14 | awk '{if($2 != "" ) printf $0" ";}' FS=";"  > station_height.csv
    file="station_height.csv"
    echo "poulou"
    #trait_argument_d_country $2 $3 $4 $5 $file
    ./exec station_height.csv gnuplot_height.csv 4 2
    #rm à faire 
     #cut -d, -f1,2,14,15 $1 > station_height.csv #faut je check si c est virgule ou point virgule
     #file="station_height.csv"
     #trait_argument_d_country $file $3 $4 $5 ;
fi



if [ $9 -eq 2]; then
tail +2 $1 | cut -d';' -f2,7 | awk '{if($2 != "" ) printf $0" ";}' FS=";"  > station_pres_date.csv
awk '{split($1,ddate,"T") ; split(ddate[1],fdate,"/"); split(ddate[2],hdate,":");  all=sprintf("%d%d%d%d", fdate[1], fdate[2], fdate[3], hdate[1]);   print all";"$2;}' FS=";"  station_pres_date.csv>  station_pres_date.csv
#pour envoyer les date correctement avl3, avl2 pareil juste change $2 en $1
./exec station_pres_date.csv gnuplot_pres_date.csv 5 1
fi


if [ "$7" = "1" ]; then
# test
fi
if [ $9 -eq 1 ]; then
    tail +2 $1 | cut -d";" -f1,7 | awk '{if($2 != "" ) printf $0" ";}' FS=";" > station_pres_ave.csv
    echo "rolo"
    ./exec station_pres_ave.csv gnuplot_pres_ave.csv 3 1
    #gnuplot pression_moyenne.sh
fi
if [ ${@: -1} -eq 1 ]; then
    tail +2 $1 | cut -d";" -f1,11 | awk '{if($2 != "" ) printf $0" ";}' FS=";" > station_temp_ave.csv
    echo "rolo"
    ./exec station_temp_ave.csv gnuplot_temp_ave.csv 3 1
    #gnuplot pression_moyenne.sh
fi


}

trait_argument_d_country() {
    

    if [ $1 -eq 1 ]; then
        start=$(echo $2 | sed -e "s|/||g")
        finish=$(echo $3 | sed -e "s|/||g")
        awk -v st=$start -v fn=$finish '{split($2,ddate,"T") ; split(ddate[1],compil,"/"); all=sprintf("%d%d%d", compil[1], compil[2], compil[3]); if(all < fn && all > st) print $0;}' FS=";" $5 > $5#cut les dates
                
    fi
    case $4 in 

        1) awk '{split($10,fr,","); if(fr[1] < 51.2 && fr[1] > 41.3 && fr[2] > -5 && fr[2] < 9.7) print $0;}' FS=";" $5 > $5

        #cut en fonction de fr
        ;;
        2) awk '{split($10,fr,","); if(fr[1] < 6 && fr[1] > 2 && fr[2] > -55 && fr[2] < -50) print $0;}' FS=";" $5 > $5
        #cut en fonction guyanne fr
        ;;
        3)awk '{split($10,fr,","); if(fr[1] < 47.2 && fr[1] > 46.5 && fr[2] > -57 && fr[2] < -56) print $0;}' FS=";" $5 > $5
        #cut en fonction de Saint-Pierre et Miquelon
        ;;
        4)awk '{split($10,fr,","); if(fr[1] < 19 && fr[1] > 11 && fr[2] > -66 && fr[2] < -58) print $0;}' FS=";" $5 > $5
        #cut antilles
        ;;
        5)awk '{split($10,fr,","); if(fr[1] < -60) print $0;}' FS=";" $5 > $5
        #cut antarctique mais pas fini ask to ptrofesor
        ;;
        6)awk '{split($10,fr,","); if(fr[1] < 6 && fr[1] > 2 && fr[2] > -57 && fr[2] < -50) print $0;}' FS=";" $5 > $5
        
        ;;
        *)
        ;;
    esac


}




    make -f Makefile.mak
    
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
    for k in $@; do

        if [ $after -eq 1 ]; then 
            if file_check $k; then
                
             head -1 $k | sed 's/.*/\U&/' | sed -e "s/ //g" > check_field.csv #probleme $1 pas forcement fichier
             
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
    if [ ! $(grep STATION check_field.csv) ]; then
        echo "the field station don't exist"
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
                    w) if [ ! $(grep DIRECTIONDUVENTMOYEN10MN check_field.csv) ] || [ ! $(grep -x VITESSEDUVENTMOYEN10MN check_field.csv) ] ; then
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
                          avl) avl=1 #avl verif qu il en a pas mis 2 et l envoyer apres au programme
                            ;;
                            abr) abr=1 #abr
                           ;;
                            tab) tab=1 #list
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
                        if [ ! $(grep COORDONNEES check_field.csv) ]; then
                            echo "the field coordonnees don't exist"
                            x=0;
                        else
                            x=1
                        fi
                    ;;
                    G)  if [ $x -ne 0 ]; then
                            echo "you need to choose only one location"
                            exit 1
                        fi
                        if [ ! $(grep COORDONNEES check_field.csv) ]; then
                            echo "the field coordonnees don't exist"
                            x=0;
                        else
                            x=2
                        fi
                    ;;
                    S)  if [ $x -ne 0 ]; then
                            echo "you need to choose only one location"
                            exit 1
                        fi
                        if [ ! $(grep COORDONNEES check_field.csv) ]; then
                            echo "the field coordonnees don't exist"
                            x=0;
                        else
                            x=3
                        fi
                    ;;
                    A)  if [ $x -ne 0 ]; then
                            echo "you need to choose only one location"
                            exit 1
                        fi
                        if [ ! $(grep COORDONNEES check_field.csv) ]; then
                            echo "the field coordonnees don't exist"
                            x=0;
                        else
                            x=4
                        fi
                    ;;

                    Q)  if [ $x -ne 0 ]; then
                            echo "you need to choose only one location"
                            exit 1
                        fi
                        if [ ! $(grep COORDONNEES check_field.csv) ]; then
                            echo "the field coordonnees don't exist"
                            x=0;
                        else
                            x=5
                        fi
                    ;;
                    O)  if [ $x -ne 0 ]; then
                            echo "you need to choose only one location"
                            exit 1
                        fi
                        if [ ! $(grep COORDONNEES check_field.csv) ]; then
                            echo "the field coordonnees don't exist"
                            x=0;
                        else
                            x=6
                        fi
                    ;;
                    d)
                         if [ ! $(grep DATE check_field.csv) ]; then
                            echo "the field date don't exist"
                         fi #mettre 00
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
                        ;;
                        *) 
                        ;;
                esac
            done
            if [ $count -eq 0 ]; then
                echo "you must choose an option"
            fi
            rm check_field.csv
            trait_argument $file $d $choice1 $choice2 $x $h $m $w $p $t
