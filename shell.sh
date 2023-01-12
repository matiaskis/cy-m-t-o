#!/bin/bash
file_check() {
    if [ ! -d $1 ]; then 
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
    file=$1

    if [ $2 -eq 1 ]; then
        #cut les dates
        #créer un fichier
        hello=1
    fi
    case $2 in 

        1) #cut en fonction de fr
        ;;
        2)
        ;;
        3)
        ;;
        4)
        ;;
        5)
        ;;
        6)
        ;;
        *)
        ;;
    esac


}





    x=0
    choice1=0
    choice2=0
     while getopts "t:p:wmhf:FGSAOQd:-:" option
       do
               
               case $option in
                    #file
                    f) if ! file_check $OPTARG; then 
                        exit 1
                       else 
                            file=$OPTARG
                        fi

                    ;;
                    #height
                    h) h=1
                    ;;
                    #moisture
                    m) m=1
                    ;;
                    #wind
                    w) w=1
                    ;;
                    #pressure
                    p) if [ "$OPTARG" != "1" ] && [ "$OPTARG" != "2" ] && [ "$OPTARG" != "3"  ]; then
                            echo"p option argument must be 1 2 or 3"
                            exit 1
                        fi
                        p=1
                    ;;
                    #temperature
                    t) if [ "$OPTARG" != "1" ] && [ "$OPTARG" != "2" ] && [ "$OPTARG" != "3"  ]; then
                            echo"t option argument must be 1 2 or 3"
                            exit 1
                        fi
                        t=1
                    ;;
                    -) case $OPTARG in 
                          avl) avl=1 #avl
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
                    O)  if [ $x -ne 0 ]; then
                            echo "you need to choose only one location"
                            exit 1
                        fi
                        x=5
                    ;;
                    Q)  if [ $x -ne 0 ]; then
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
                        echo "$choice1 $choice2"
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
            trait_argument $file $d $choice1 $choice2 $x $h $m $w $p $t
