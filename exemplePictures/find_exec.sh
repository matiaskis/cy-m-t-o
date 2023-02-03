#!/bin/bash
nb_args=$#
if [ $nb_args != 2 ] || [ ! -d $1 ] ; then
echo " format de la commande : find_exec.sh repertoire "
exit 1 
date -d "$2"
for nom in $(ls $1) ; do
    if [ -x $1/$nom ] ; then 
        echo $nom
        echo $( du $1/$nom )
    fi
done