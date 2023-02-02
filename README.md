# projet CY-météo
This program is used to create graphics based on a weather data file. It uses for that a shell script and a c programm. The shell script manage all different options
possible : 

           -t1 max,min adn average temperature per station
           -p1 max,min adn average pressure per station
           -t2 average temperature per date on every station 
           -p2 average pressure per date on every station 
           -t3 every temperature per date then per station
           -w wind map for each station
           -h height per station
           -m moisture per station
           (there are no limitations for these options, you can put more than one at a time but you need at least one) 
           
           -F metropolitan france and corsica
           -G French Guiana
           -S Saint Pierre and Miquelon
           -A West Indies
           -O Indian Ocean
           -Q Antarctic
           (optionnal, and you can only choose one)
           
           -d the output graph will be between two given dates of this format : YYYY/MM/DD
            (optionnal)
           
           --avl sort the data using a avl tree
           --abr sort the data using a binary search tree
           --tab sort the data using a linked list 
           (if this option is not specified, the sorting will be done with an avl tree by default)
           
           --help if you need specification on the arguments 
           
           -f path relative to the input file 
           (this option is mandatory) 
           
the shell script also filters all the data needed by the c programm in the weather data file , relative to the option passed as an argument.
The c programm then sort all the data and give to the shell script another file with just the needed data sorted.
The shell script then uses gnuplot to create graphics.

           
to execute the programm : ./s.sh -f input_file <option> <option>
for exemple : ./s.sh -f input_file -p1 --avl -d 2012/03/24,2017/05/12
(there is no order for the specified options)
           

