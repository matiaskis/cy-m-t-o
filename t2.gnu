reset

set grid nopolar
set grid xtics mxtics ytics mytics noztics nomztics nortics nomrtics \
nox2tics nomx2tics noy2tics nomy2tics nocbtics nomcbtics
set style data line
set terminal png size 1920,1080
set title "temperature per date"
set xlabel "date"
set ylabel "temperature"
set autoscale noextend
set xtics rotate by 45 right
set xdata time
set timefmt "%d/%m/%y-%H%:%M:%S"
set format x "%d/%m/%y-%H%:%M:%S"
set xrange[*:*]
set yrange[*:*]
set output "t2.png"

plot "gnuplot_temp_date.csv" using 1:2 with lines title "temperature"

