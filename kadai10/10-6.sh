vmstat 3 | awk '{if (NR!=1) print $(NF-2); else print $NF}'
