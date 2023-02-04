reset

set terminal png size 1920, 1080
set title "temperature max, average, min"
set xlabel "station"
set ylabel "temperature"
set xrange [*:*]
set output "t1Tab.png"
set autoscale noextend
set xtics rotate by 45 right
set grid nopolar
set grid xtics mxtics ytics mytics noztics nomztics nortics nomrtics \
nox2tics nomx2tics noy2tics nomy2tics nocbtics nomcbtics
set style data lines
Shadecolor = "#80E0A080"
plot "gnuplot_temp_max.csv" using 0:3:4 with filledcurve fc rgb Shadecolor title "Shaded error region", \
"gnuplot_temp_max.csv" using 0:2:xticlabels(1) smooth mcspline lc 6 lw 2  title "average temperature"
