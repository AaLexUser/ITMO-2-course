make all
result_md=./RESULTS.md
echo "### Results:" > $result_md
echo "#### C solution:" >> $result_md
./image-sepia -c input.bmp output.bmp >> $result_md
echo "#### ASM solution:" >> $result_md
./image-sepia -a input.bmp output.bmp >> $result_md
