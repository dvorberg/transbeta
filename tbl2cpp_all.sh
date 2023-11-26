for a in *.tbl
do
    python3 tbl2cpp.py < $a > $(echo $a | sed s/.tbl/.inc/)
done
