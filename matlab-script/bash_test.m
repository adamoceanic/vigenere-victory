% Result from webcam
nn_result = "X";

bash1 = "#! /bin/bash\n";
bash2 = 'cipher_text="' + nn_result + '"\n';
bash3 = "echo $cipher_text";

bash = bash1 + bash2 + bash3;

fid = fopen('/home/sapho/portfolio-work/vigenere-victory/matlab-script/matlab_get_string.sh','wt');
fprintf(fid, bash);
fclose(fid);