set terminal gif animate delay 5 loop 0 size 1200,600
set output 'plots/point_distributions_absorb.gif

stats "data/point_distribution_absorb.dat" using 1 nooutput

set xrange [-60:60]
set yrange [0:600]

set style data boxes
set boxwidth 1
set style fill solid



do for [i=0:int(STATS_blocks)-2]{
  set multiplot layout 1,2

  set title "random walk"
  plot "data/point_distribution_absorb.dat" in i with boxes title "point count"

  set title "random walk with random step"
  plot "data/point_distribution_random_step_absorb.dat" in i with boxes title "point count"
  unset multiplot
}

set output