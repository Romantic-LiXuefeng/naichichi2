�t���[�`���[�z�[���R���g���[���[(FHC)
=============

�����F���ɂ��z�[���R���g���[������������t���[�`���[�z�[���R���g���[���[�̃\�[�X�R�[�h�ł��B  
�����A�V�X�^���g�Ƃ��A�X�}�[�g�X�s�[�J�[�Ƃ��ł��B  
�����œ��삷��X�}�[�g�z�[���������ł��܂��B  


�\�t�g�E�F�A�� GPL �Ń��C�Z���X�Ō��J���܂��B  
�����R�ɂ��g�����������B  
2012�N����J�����Ă���̂ŁA�኱�Â����̂�����܂��B  
�Â��Ă��Aopenssl�̓o�O�C���̃p�b�`�������Ƃ��ĂĂ܂��̂ł����S���������B  


�����
=============

windows�� Linux �œ��삵�܂��B(�N���X�v���b�g�t�H�[���ł�)  
VS2010�ȍ~�ŃR���p�C���ł��܂��B  
gcc �́Aver4�n�������瓮���Ǝv���܂��B  

VS2013�����́A std::thread���Ȃ��̂� boost::thread�ő�p���܂��B  
����ȊO�̏����n�ł́A std::thread �𗘗p���܂��B  

�܂܂����e  
=============
* �����F���G���W��  
* ���������G���W��  
* web�T�[�o�Ɖ��  
* �����G���W��  
* �����䓯��  
* javascript���s�����n  
* Homekit�G�~�����[�V����  
* HEMS(EcoNetLite)  
* UPNP(SSDP)  
* sip(���X�̗��R�ɂ�薳���ɂ��Ă��܂�)  
* ���x���x�Z���T�[(�������n�[�h���Ȃ��Ɠ����Ȃ�)�ƁA�O���t
* �w�K�����R���̎�M���A���M��(�������n�[�h���Ȃ��Ɠ����Ȃ�)
* ���̑����낢��  
* ��͂�arm�ł������܂��B  


�g����  
=============
�ȉ��̊��ŁA�R���p�C�����Ă��������B  
Windows + VS2010 + boost(VS2010�ɂ� std::thread���Ȃ�����boost�ő�p)  
Windows + VS2013�ȍ~  
Linux + gcc ver4  


windows�ł́A naichichi2.sln ���J���� F5�r���h���Ă��������B  


linux ubuntu�ł���΁A�K�v�ȃ\�t�g�E�F�A����ꂽ��ŁA  
apt-get install gcc g++  
apt-get install flex uuid uuid-dev libasound2 libasound2-dev mplayer  
  
sh build.sh  

or  

sh build.sh arm  
sh build.sh x86  
sh build.sh ia32  

���������R���p�C�����I�������A  

cd naichichi2  
./naichichi2_client  

or  

cd naichichi2  
./naichichi2_client --nostdout  

or  

�����A���Ȃ����A�ȉ��ɓ���Ă���Ȃ�΁A���ꂪ���p�ł��܂��B  
 /home/rti/naichichi2/  
  
cd /home/rti/naichichi2/naichichi2/config/linuxboot  
./naichichi2_zaoriku_client.sh  


�R���p�C�����Đ��������v���Z�X  
naichichi2_client �����s������Aweb�T�[�o���N������̂ŁA�u���E�U����A�N�Z�X���Ă��������B  
http://127.0.0.1/  


web��ʂɃA�N�Z�X����ɂ́A�A�J�E���g�o�^���K�v�ł��B  
https://fhc.rti-giken.jp/welcome/newregist  

�A�J�E���g�͖����ł��B  
�����A���̂��������ł����͍L���ł��o�������E�E�E  


�}�j���A��
=============
�}�j���A���͂�����ɂ���܂��B  
�`���[�g���A��  
https://rti-giken.jp/fhc/help/howto/  
  
��ʃ��t�@�����X  
https://rti-giken.jp/fhc/help/ref/  
  
�X�N���v�g���t�@�����X  
https://rti-giken.jp/fhc/help/ref/  
  
WebAPI���t�@�����X  
https://rti-giken.jp/fhc/help/ref/setting_webapi.html  


�����I�Ƀf�o�C�X���Ȃ��Ƃł��Ȃ��w�K�����R���ȊO�̏����𓮂������Ƃ��ł��܂��B  

�y���������l�́E�E�E
=============

�w�K�����R�������ڂ��ꂽ�����ɓ��삷��n�[�h�E�F�A���A�����炩�甃���܂��B  
�y���������l�́A�����炩��ǂ����B 
���Ȃ�L�����y�[���� 26,800�~�ł��B

https://rti-giken.jp/  


��� :: rti (rti@rti-giken.jp)  
