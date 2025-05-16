set terminal gif animate delay 5 loop 0 size 1200,600
set output 'plots/point_distribution_ds.gif

stats "data/point_distribution_ds.dat" using 1 nooutput

set xrange [-200:200]
set yrange [0:600]

set style data boxes
set boxwidth 1
set style fill solid

do for [i=0:int(STATS_blocks)-2]{
  plot "data/point_distribution_ds.dat" in i with boxes title "point count"
}

set output