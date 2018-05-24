#ifndef __IVR_UTIL_H
#define __IVR_UTIL_H

/** linux C������ο�

��1�� �ַ����Ժ���
isalnum(�����ַ��Ƿ�ΪӢ����ĸ������)
isalpha(�����ַ��Ƿ�ΪӢ����ĸ)
isascii(�����ַ��Ƿ�ΪASCII���ַ�)
isblank(�����ַ��Ƿ�Ϊ�ո��ַ�)
iscntrl(�����ַ��Ƿ�ΪASCII��Ŀ����ַ�)
isdigit(�����ַ��Ƿ�Ϊ����������)
isgraph(�����ַ��Ƿ�Ϊ�ɴ�ӡ�ַ�)
islower(�����ַ��Ƿ�ΪСдӢ����ĸ)
isprint(�����ַ��Ƿ�Ϊ�ɴ�ӡ�ַ�)
isspace(�����ַ��Ƿ�Ϊ�ո��ַ�)
ispunct(�����ַ��Ƿ�Ϊ�����Ż��������)
isupper(�����ַ��Ƿ�Ϊ��дӢ����ĸ)
isxdigit(�����ַ��Ƿ�Ϊ16��������)

��2�� ����ת������
atof(���ַ���ת���ɸ�������)
atoi(���ַ���ת����������)
atol(���ַ���ת���ɳ�������)
ecvt(����������ת�����ַ�����ȡ��������)
fcvt(����������ת��Ϊ�ַ�����ȡ��������)
gcvt(����������ת��Ϊ�ַ�����ȡ��������)
strtod(���ַ���ת���ɸ�������)
strtol(���ַ���ת���ɳ�������)
strtoul(���ַ���ת�����޷��ų�������)
toascii(��������ת���ɺϷ���ASCII���ַ�)
tolower(����д��ĸת����Сд��ĸ)
toupper(��Сд��ĸת���ɴ�д��ĸ)

��3�� �ڴ����ú���
alloca(�����ڴ�ռ�)
brk(�ı������ֽڵķ�Χ)
calloc(�����ڴ�ռ�)
free(�ͷ�ԭ�����õ��ڴ�)
getpagesize(ȡ���ڴ��ҳ��С)
malloc(�����ڴ�ռ�)
mmap(�����ڴ�ӳ��)
munmap(����ڴ�ӳ��)
realloc(���ļ����õ��ڴ�ռ�)
sbrk(���ӳ�����õ����ݿռ�)

��4�� ʱ�亯��
asctime(��ʱ����������ַ�����ʽ��ʾ)
clock(ȡ�ý���ռ��CPU�Ĵ�Լʱ��)
ctime(��ʱ����������ַ�����ʽ��ʾ)
difftime(����ʱ����)
ftime(ȡ��Ŀǰ��ʱ�������)
gettimeofday(ȡ��Ŀǰ��ʱ��)
gmtime(ȡ��Ŀǰ��ʱ�������)
localtime(ȡ�õ���Ŀǰ��ʱ�������)
mktime(��ʱ��ṹ����ת���ɾ���������)
settimeofday(����Ŀǰ��ʱ��)
strftime(��ʽ�����ں�ʱ��)
time(ȡ��Ŀǰ��ʱ��)
tzset(����ʱ���Թ�ʱ��ת��)

��5�� �ַ���������
bcmp(�Ƚ��ڴ�����)
bcopy(�����ڴ�����)
bzero(��һ���ڴ�����ȫ��Ϊ��)
ffs(��һ�������в��ҵ�һ��ֵΪ���λ)
index(�����ַ����е�һ�����ֵ�ָ���ַ�)
memccpy(�����ڴ�����)
memchr(��ĳһ�ڴ淶Χ�в���һ�ض��ַ�)
memcmp(�Ƚ��ڴ�����)
memcpy(�����ڴ�����)
memfrob(���ڴ��������)
memmove(�����ڴ�����)
memset(��һ���ڴ�ռ�����ĳֵ)
rindex(�����ַ��������һ�����ֵ�ָ���ַ�)
strcasecmp(���Դ�Сд�Ƚ��ַ���)
strcat(�������ַ���)
strchr(�����ַ����е�һ�����ֵ�ָ���ַ�)
strcmp(�Ƚ��ַ���)
strcoll(����Ŀǰ������ַ����д������Ƚ��ַ���)
strcpy(�����ַ���)
strcspn(�����ַ�������������ָ���ַ������ݵ��ַ���)
strdup(�����ַ���)
strfry(��������ַ����ڵ��ַ�)
strlen(�����ַ�������)
strncasecmp(���Դ�Сд�Ƚ��ַ���)
strncat(�������ַ���)
strncmp(�Ƚ��ַ���)
strncpy(�����ַ���)
strpbrk(�����ַ����е�һ�����ֵ�ָ���ַ�)
strrchr(�����ַ��������һ�����ֵ�ָ���ַ�)
strspn(�����ַ�������������ָ���ַ������ݵ��ַ���)
strstr(��һ�ַ����в���ָ�����ַ���)
strtok(�ָ��ַ���)

��6�� ��ѧ���㺯��
abs(�����������ľ���ֵ)
acos(ȡ�����Һ���ֵ)
asin(ȡ�����Һ���ֵ)
atan(ȡ�����к���ֵ)
atan2(ȡ�÷����к���ֵ)
ceil(ȡ��С�ڲ�������С������)
cos(ȡ���Һ���ֵ)
cosh(ȡ˫�������Һ���ֵ)
div(ȡ�����������������̼�����)
exp(����ָ��)
fabs(���㸡�������ľ���ֵ)
frexp(������������Ϊ������ָ��)
hypot(����ֱ��������б�߳�)
labs(���㳤�������ľ���ֵ)
ldexp(����2�Ĵη�ֵ)
ldiv(ȡ�����������������̼�����)
log(������eΪ�׵Ķ���ֵ)
log10(������10Ϊ�׵Ķ���ֵ)
modf(�����������ֽ��������С��)
pow(����η�ֵ)
sin(ȡ���Һ���ֵ)
sinh(ȡ˫�������Һ���ֵ)
sqrt(����ƽ����ֵ)
tan(ȡ���к���ֵ)
tanh(ȡ˫�������к���ֵ)

��7�� �û����麯��
cuserid(ȡ���û��ʺ�����)
endgrent(�ر����ļ�)
endpwent(�ر������ļ�)
endutent(�ر�utmp�ļ�)
fgetgrent(��ָ�����ļ�����ȡ���ʽ)
fgetpwent(��ָ�����ļ�����ȡ�����ʽ)
getegid(ȡ����Ч����ʶ����)
geteuid(ȡ����Ч���û�ʶ����)
getgid(ȡ����ʵ����ʶ����)
getgrent(�����ļ��ļ���ȡ���ʺŵ�����)
getgrgid(�����ļ���ȡ��ָ��gid������)
getgrnan(�����ļ���ȡ��ָ���������)
getgroups(ȡ�������)
getlogin(ȡ�õ�¼���û��ʺ�����)
getpw(ȡ��ָ���û��������ļ�����)
getpwent(�������ļ���ȡ���ʺŵ�����)
getpwnam(�������ļ���ȡ��ָ���ʺŵ�����)
getpwuid(�������ļ���ȡ��ָ��uid������)
getuid(ȡ����ʵ���û�ʶ����)
getutent(��utmp�ļ���ȡ���ʺŵ�¼����)
getutid(��utmp�ļ��в����ض��ļ�¼)
getutline(��utmp�ļ��в����ض��ļ�¼)
initgroups(��ʼ�����嵥)
logwtmp(��һ��¼���ݼ�¼��wtmp�ļ�)
pututline(��utmp��¼д���ļ�)
setegid(������Ч����ʶ����)
seteuid(������Ч���û�ʶ����)
setfsgid(�����ļ�ϵͳ����ʶ����)
setfsuid(�����ļ�ϵͳ���û�ʶ����)
setgid(������ʵ����ʶ����)
setgrent(��ͷ��ȡ���ļ��е�������)
setgroups(���������)
setpwent(��ͷ��ȡ�����ļ��е��ʺ�����)
setregid(������ʵ����Ч����ʶ����)
setreuid(������ʵ����Ч���û�ʶ����)
setuid(������ʵ���û�ʶ����)
setutent(��ͷ��ȡutmp/�ļ��еĵ�¼����)
updwtmp(��һ��¼���ݼ�¼��wtmp�ļ�)
utmpname(����utmp�ļ�·��)

��8�� ���ݼ��ܺ���
crypt(����������ݱ���)
getpass(ȡ��һ��������)

��9�� ���ݽṹ����
bsearch(��Ԫ����)
hcreate(������ϣ��)
hdestory(ɾ����ϣ��)
hsearch(��ϣ������)
insque(����һ��Ŀ��������)
lfind(��������)
lsearch(��������)
qsort(���ÿ���������������)
rremque(�Ӷ�����ɾ��һ��Ŀ)
tdelete(�Ӷ�������ɾ������)
tfind(����������)
tsearch(������)
twalk(�߷ö�����)

��10�� ���������
drand48(����һ�����ĸ����������)
erand48(����һ�����ĸ����������)
initstate(���������״̬����)
jrand48(����һ���������������)
lcong48(����48λ��������������)
lrand48(����һ�����ĳ����������)
mrand48(����һ�������������)
nrand48(����һ�����ĳ����������)
rand(���������)
random(���������)
seed48(����48λ��������������)
setstate(���������״̬����)
srand(�������������)
srand48(����48λ��������������)
srandom(�������������)

��11�� ����I��O����
close(�ر��ļ�)
creat(�����ļ�)
dup(�����ļ�������)
dup2(�����ļ�������)
fcntl(�ļ������ʲ���)
flock(�����ļ���������)
fsync(������������д�ش���)
lseek(�ƶ��ļ��Ķ�дλ��)
mkstemp(����Ψһ����ʱ�ļ�)
open(���ļ�)
read(�ɼ��򿪵��ļ���ȡ����)
sync(������������д�ش���)
write(������д���Ѵ򿪵��ļ���)

��12�� ��׼I��O����
clearerr(����ļ����Ĵ������)
fclose(�ر��ļ�)
fdopen(���ļ�������תΪ�ļ�ָ��)
feof(����ļ����Ƿ�������ļ�β)
fflush(���»�����)
fgetc(���ļ��ж�ȡһ���ַ�)
fgetpos(ȡ���ļ����Ķ�ȡλ��)
fgets(���ļ��ж�ȡһ�ַ���)
fileno(�����ļ�����ʹ�õ��ļ�������)
fopen(���ļ�)
fputc(��һָ���ַ�д���ļ�����)
fputs(��һָ�����ַ���д���ļ���)
fread(���ļ�����ȡ����)
freopen(���ļ�)
fseek(�ƶ��ļ����Ķ�дλ��)
fsetpos(�ƶ��ļ����Ķ�дλ��)
ftell(ȡ���ļ����Ķ�ȡλ��)
fwrite(������д���ļ���)
getc(���ļ��ж�ȡһ���ַ�)
getchar(�ɱ�׼�����豸�ڶ���һ�ַ�)
gets(�ɱ�׼�����豸�ڶ���һ�ַ���)
mktemp(����Ψһ����ʱ�ļ��ļ���)
putc(��һָ���ַ�д���ļ���)
putchar(��ָ�����ַ�д����׼����豸)
puts(��ָ�����ַ���д����׼����豸)
rewind(�����ļ����Ķ�дλ��Ϊ�ļ���ͷ)
setbuf(�����ļ����Ļ�����)
setbuffer(�����ļ����Ļ�����)
setlinebuf(�����ļ���Ϊ���Ի�����)
setvbuf(�����ļ����Ļ�����)
tmpfile(������ʱ�ļ�)
ungetc(��һָ���ַ�д���ļ�����)

��13�� ���̼����̿���
abort(���쳣��ʽ��������)
assert(�����Ե���������������ֹ����)
atexit(���ó�����������ǰ���õĺ���)
execl(ִ���ļ�)
execle(ִ���ļ�)
execlp(��PATH���������в����ļ���ִ��)
execv(ִ���ļ�)
execve(ִ���ļ�)
execvp(ִ���ļ�)
exit(������������)
_exit(��������ִ��)
fork(����һ���µĽ���)
getpgid(ȡ�ý�����ʶ����)
getpgrp(ȡ�ý�����ʶ����)
getpid(ȡ�ý���ʶ����)
getppid(ȡ�ø����̵Ľ���ʶ����)
getpriority(ȡ�ó������ִ������Ȩ)
longjmp(��ת��ԭ��setjmp����Ķ�ջ����)
nice(�ı��������˳��)
on��exit(���ó�����������ǰ���õĺ���)
ptrace(����׷��)
setjmp(����Ŀǰ��ջ����)
setpgid(���ý�����ʶ����)
setpgrp(���ý�����ʶ����)
setpriority(���ó������ִ������Ȩ)
siglongjmp(��ת��ԭ��sigsetjmp����Ķ�ջ����)
sigsetjmp(����Ŀǰ��ջ����)
system(ִ��shell����)
wait(�ȴ��ӽ����жϻ����)
waitpid(�ȴ��ӽ����жϻ����)

��14�� ��ʽ�������������
fprintf(��ʽ������������ļ�)
fscanf(��ʽ���ַ�������)
printf(��ʽ���������)
scanf(��ʽ���ַ�������)
snprintf(��ʽ���ַ�������)
sprintf(��ʽ���ַ�������)
sscanf(��ʽ���ַ�������)
vfprintf(��ʽ������������ļ�)
vfcanf(��ʽ���ַ�������)
vprintf(��ʽ���������)
vscanf(��ʽ���ַ�������)
vsnprintf(��ʽ���ַ�������)
vsprintf(��ʽ���ַ�������)
vsscanf(��ʽ���ַ�������)

��15�� �ļ���Ŀ¼����
access(�ж��Ƿ���д�ȡ�ļ���Ȩ��)
alphasort(����ĸ˳������Ŀ¼�ṹ)
chdir(�ı䵱ǰ�Ĺ���Ŀ¼)
chmod(�ı��ļ���Ȩ��)
chown(�ı��ļ���������)
chroot(�ı��Ŀ¼)
closedir(�ر�Ŀ¼)
fchdir(�ı䵱ǰ�Ĺ���Ŀ¼)
fchmod(�ı��ļ���Ȩ��)
fchown(�ı��ļ���������)
fstat(���ļ�������ȡ���ļ�״̬)
ftruncate(�ı��ļ���С)
ftw(����Ŀ¼��)
get_current_dir_name(ȡ�õ�ǰ�Ĺ���Ŀ¼)
getcwd(ȡ�õ�ǰ�Ĺ���Ŀ¼)
getwd(ȡ�õ�ǰ�Ĺ���Ŀ¼)
lchown(�ı��ļ���������)
link(�����ļ�����)
lstat(���ļ�������ȡ���ļ�״̬)
nftw(����Ŀ¼��)
opendir(��Ŀ¼)
readdir(��ȡĿ¼)
readlink(ȡ�÷���������ָ���ļ�)
realpath(�����Ŀ¼·��ת���ɾ���·��)
remove(ɾ���ļ�)
rename(�����ļ����ƻ�λ��)
rewinddir(�����ȡĿ¼��λ��Ϊ��ͷλ��)
scandir(��ȡ�ض���Ŀ¼����)
seekdir(�����»ض�ȡĿ¼��λ��)
stat(ȡ���ļ�״̬)
symlink(�����ļ���������)
telldir(ȡ��Ŀ¼���Ķ�ȡλ��)
truncate(�ı��ļ���С)
umask(���ý������ļ�ʱ��Ȩ������)
unlink(ɾ���ļ�)
utime(�޸��ļ��Ĵ�ȡʱ��͸���ʱ��)
utimes(�޸��ļ��Ĵ�ȡʱ��͸���ʱ��)

��16�¡��źź���
alarm(�����źŴ�������)
kill(�����źŸ�ָ���Ľ���)
pause(�ý�����ֱͣ���źų���)
psignal(�г��ź�������ָ���ַ���)
raise(�����źŸ�Ŀǰ�Ľ���)
sigaction(��ѯ�������źŴ���ʽ)
sigaddset(����һ���ź����źż�)
sigdelset(���źż���ɾ��һ���ź�)
sigemptyset(��ʼ���źż�)
sigfillset(�������źż������źż�)
sigismember(����ĳ���ź��Ƿ��Ѽ������źż���)
signal(�����źŴ���ʽ)
sigpause(��ֱͣ���źŵ���)
sigpending(��ѯ�����õ��ź�)
sigprocmask(��ѯ�������ź�����)
sigsuspend(��ֱͣ���źŵ���)
sleep(�ý�����ִͣ��һ��ʱ��)
isdigit(�����ַ��Ƿ�Ϊ����������)

��17�� ��������
ferror(����ļ����Ƿ��д�����)
perror(��ӡ������ԭ����Ϣ�ַ���)
streror(���ش���ԭ��������ַ���)

��18�� �ܵ���غ���
mkfifo(���������ܵ�)
pclose(�رչܵ�I��O)
pipe(�����ܵ�)
popen(�����ܵ�I/O)

��19�� Socket��غ���
accept(����socket����)
bind(��socket��λ)
connect(����socket����)
endprotoent(��������Э�����ݵĶ�ȡ)
endservent(��������������ݵĶ�ȡ)
gethostbyaddr(��IP��ַȡ����������)
gethostbyname(����������ȡ����������)
getprotobyname(������Э������ȡ��Э������)
getprotobynumber(������Э����ȡ��Э������)
getprotoent(ȡ������Э������)
getservbyname(������ȡ��������������)
getservbyport(��port����ȡ��������������)
getservent(ȡ������������������)
getsockopt(ȡ��socket״̬)
herror(��ӡ���������ԭ����Ϣ�ַ���)
hstrerror(�����������ԭ��������ַ���)
htonl(��32λ�����ַ�˳��ת���������ַ�˳��)
htons(��16λ�����ַ�˳��ת���������ַ�˳��)
inet_addr(�������ַת����������Ƶ�����)
inet_aton(�������ַת����������Ƶ�����)
inet_ntoa(����������Ƶ�����ת���������ַ)
listen(�ȴ�����)
ntohl(��32λ�����ַ�˳��ת���������ַ�˳��)
ntohs(��16λ�����ַ�˳��ת���������ַ�˳��)
recv(��socket��������)
recvfrom(��socket��������)
recvmsg(��socket��������)
send(��socket��������)
sendmsg(��socket��������)
sendto(��socket��������)
setprotoent(������Э��������ļ�)
setservent(�������������������ļ�)
setsockopt(����socket״̬)
shutdown(��ֹsocketͨ��)
socket(����һ��socketͨ��)

��20�� ����ͨ��(IPC)����
ftok(���ļ�·���ͼƻ�����תΪSystem VIPCkey)
msgctl(������Ϣ���е�����)
msgget(������Ϣ����)
msgrcv(����Ϣ���ж�ȡ��Ϣ)
msgsnd(����Ϣ������Ϣ����)
semctl(�����źŶ��еĲ���)
semget(�����źŶ���)
semop(�źŴ���)
shmat(attach�����ڴ�)
shmctl(���ƹ����ڴ�Ĳ���)
shmdt(detach�����ڴ�)
shmget(���ù����ڴ�)

��21�� ��¼����
closelog(�ر���Ϣ��¼)
openlog(׼������Ϣ��¼)
syslog(����Ϣ��¼��ϵͳ��־�ļ�)

��22�� ������������
getenv(ȡ�û�����������)
putenv(�ı�����ӻ�������)
setenv(�ı�����ӻ�������)
unsetenv(���������������)

*/

#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <signal.h>
#include <cctype>
#include <functional>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>
#include <sys/time.h>
#include <sys/stat.h>

#ifndef win32
    typedef struct _SYSTEMTIME { 
        unsigned short wYear;
        unsigned short wMonth;
        unsigned short wDay;
        unsigned short wDayOfWeek;
        unsigned short wHour;
        unsigned short wMinute;
        unsigned short wSecond;
        unsigned short wMilliseconds;
    } SYSTEMTIME;
#endif

/**** ���ڳ��ø�ʽ
    * %Y ������������ֱ�ʾ������λ�������� 2012
    * %y ��λ���ֱ�ʾ��� (��Χ�� 00 �� 99)
    * %m �·ݵ����� (��Χ�� 1 �� 12)
    * %d ���ڣ������ֱ�ʾ���µĵڼ��� (��ΧΪ 00 �� 31)
    * %H �� 24 Сʱ�����ֱ�ʾСʱ�� (��ΧΪ 00 �� 23)
    * %M ����
    * %S ����
    */
#define LONG_DATE_FORMAT        "%Y-%m-%d"
#define SHORT_DATE_FORMAT       "%Y%m%d"
#define LONG_TIME_FORMAT        "%H:%M:%S"
#define SHORT_TIME_FORMAT       "%H%M%S"
#define LONG_DATETIME_FORMAT    "%Y-%m-%d %H:%M:%S"
#define SHORT_DATETIME_FORMAT   "%Y%m%d%H%M%S"
#define LONG_MILLSEC_FORMAT     "%04d-%02d-%02d %02d:%02d:%02d.%03d"
#define SHORT_MILLSEC_RORMAT    "%02d:%02d:%02d.%03d"
#define SHORT_YEARMONTH_FORMAT  "%Y%m"
#define LONG_YEARMONTH_FORMAT   "%Y-%m"
#define LONG_DATETIME_LEN       21
#define SHORT_DATETIME_LEN      16

const char InternationalNo[44][12]={"010086","01010086","010100086","1010086",
                                    "07701010086","07711010086","07721010086",
                                    "07731010086","07741010086","07751010086",
                                    "07761010086","07771010086","07781010086",
                                    "07791010086","7701010086","7711010086",
                                    "7721010086","7731010086","7741010086",
                                    "7751010086","7761010086","7771010086",
                                    "7781010086","7791010086","077010086",
                                    "077110086","077210086","077310086",
                                    "077410086","077510086","077610086","077710086",
                                    "077810086","077910086","77010086", "77110086",
                                    "77210086","77310086","77410086","77510086",
                                    "77610086","77710086","77810086","77910086"
                                   }; //ȫ���������κ���
const char DeputyNo[45][12]={"13977186988","13807887578","15907816565","13807813003",
                             "13877598968","13978682666","13907861994","13977126268",
                             "13607716699","13807879983","13977136118","13878888298",
                             "13878830699","13907862288","13597006808","13788502399",
                             "13977107666","13907717625","13878802088","13607816098",
                             "13978598753","13607857666","13977597888","13978462668",
                             "13877419137","13977486098","13877419531","13907743391",
                             "13977852888","13607784500","13877236282","13907725662",
                             "13907726058","13878206088","13607728668","13977282139",
                             "13788735721","15807736666","13877768935","13768108569",
                             "13877756990","13507799288","13737698999","13807762618",
                             "13877112999"}; //�˴�������
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
int splitCalledNo(char* calledNo);
short adjustUserBrand(char *UserBrand, char *VipFlag);
int getCurrDay();
int getCurrMonth();
int getCurrYear();
//������һ����һ�µ�����
int getMonthDays(int iYear, int iMonth);
void getLocalSysTime(SYSTEMTIME* lpSystemTime);
void getMillSecBuffer(char *szBuf);
size_t getDTBuffer( char *szBuf, const char *szFmt = LONG_DATE_FORMAT );
int getlocalIp(char* localIp);
// added by wangtao at 2014-02-12 XQ2014012371349 �����Ż�IVRͨ����¼����TEL_ORGCALLED�ֶλ�ȡIP��ַ������
int getConfigLocalIp (const std::string &strCfgPath, char *pstrLocalIp);
// end (added by wangtao at 2014-02-12 XQ2014012371349 �����Ż�IVRͨ����¼����TEL_ORGCALLED�ֶλ�ȡIP��ַ������)
//�첽д��־��ͬ���Ļ����Բο�ivrLogger.cpp�����LogAppend
void AsynWriteFile(char* FilePath, char* FileData);
void AsynLogAppend(char* FilePath, char *szfmt, ...);
//���ַ�������߽�ȡn���ַ�
char * leftStr(char *dst,char *src, int n);
//���ַ������м��ȡn���ַ�: nΪ���ȣ�mΪλ��
char * midStr(char *dst,char *src, int n,int m);
//���ַ������ұ߽�ȡn���ַ�
char * rightStr(char *dst,char *src, int n);
bool isACMobileNo(char* PhoneNo); //012582 + MobileNo
bool isMobileNo(char* PhoneNo);  //�ƶ�����
//���������Ĺ������ε绰�������˴�������
bool isInternationalNo(char* PhoneNo);
bool isLeapYear(int iYear);
//returnTime���ص��ӳ�ʱ��
void getRelativeTime(long iSeconds, char* returnTime);
//�ж�һ���ַ����Ƿ����ִ�
bool isNumber(char* strString);
int getDgSkill(char *skill,int iFeeArea );
int skillGroupSorted(char* skillGroup);
int parseIdcard(char *Idcard,int type,char *changedId);
int splitPhoneNo(char* phoneNo);
int getCalledArea(char *CalledNo, char *FeeArea);
//�ָ�һ���ַ���������ֵ��ʾ�ɹ�ʧ��
bool splitString(char* strString,char division,char* subStr1,char* substr2);
//�滻�ַ�����һ�������ַ���Ϊָ���ַ���
int strreplace(char *sSrc, char *sMatchStr, char *sReplaceStr);
//�滻�ַ��������������ַ���Ϊָ���ַ���
int strrep(char *sSrc, char *sMatchStr, char *sReplaceStr);
int AnalyseNodeCode(char *nodeCode,char* busiCode,char*type);
bool isSelfBusiPhone(char* CalledNo);
int  getGprsProdId(char* GprsName,char* FeeArea,char* ProdId);
int  getCmdByProd(char* ProdId,char* BusiType,char* CmdStr,char* Descript,char* isChecked);
void NumToCHS(int num, char* ch);
int makeDirectory(const char *filePath);
int increaseMonth(int YearMonth, int NumberOfMonths);
//��ʱnMicroSeconds���룬���ȵ�΢��
void DelayMicroSeconds(long nMicroSeconds);

#endif
