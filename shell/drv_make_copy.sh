#=======================================================================================
#	FileName    : 
#	Description : Make Drv
#       Date:         2010/04/27
#=======================================================================================

source ./env_entry.sh

dir=$DBG_DRV_PATH

#until ["$get_key" = "E"] || ["$get_key" = "e"] # for exit
#do

clear
#if [ "$DBG_SYN_XP2LI" = "y" ]; then
#echo "######### execute Syn_file_XP2Li.sh ##########"
#cd  $DBG_SHELL_PATH ; pwd
#sh ./Syn_file_XP2Li.sh
#fi


echo -e "\033[44;37m ----build soc ko---- \033[0m"
cd  $dir/$DBG_SOC ; pwd          # ";"  do when ok or not   "&&" do when first no err
make modules -j16 > build_log

if [ $? = 0 ]; then
	echo "Make SocKo Successful!"
else
	echo -e "\033[41;37m +++++++++ soc error codes +++++++++ \033[0m"
	make modules 2 &> err_log # 错误信息ID 2
	grep -C 1 "error:" err_log
	echo -e "\033[41;37m --------- soc error codes --------- \033[0m"
	read get_key
fi


#read get_key

echo -e "\033[44;37m ----build drv ko---- \033[0m"
cd  $dir ; pwd          # ";"  do when ok or not   "&&" do when first no err
make modules -j16 > build_log

if [ "$?" = "0" ]; then
	echo -e "\033[42;37m Make  Successful\033[0m"
 #       echo "run copy_rel.sh"
	cd  $DBG_SHELL_PATH ; pwd
#	sh ./copy_rel.sh  > copy_log
else
	echo -e "\033[41;37m +++++++++ drv error codes +++++++++ \033[0m"
	make modules 2 &> err_log # 错误信息ID 2
	grep -C 1 "error:" err_log
	echo -e "\033[41;37m --------- drv error codes --------- \033[0m"
	read get_key
fi


#if [ "$DBG_SYN_LI2XP" = "y" ]; then
#echo "######### execute Syn_file_Li2XP.sh ##########"
#cd  $DBG_SHELL_PATH ; pwd
#sh ./Syn_file_li2XP.sh
#fi

#read get_key
#done

