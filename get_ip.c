#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char *argv[])

{
    struct ifaddrs *ifaddr, *ifa;
    int family, s;
    char host[NI_MAXHOST];

    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs");
	printf("\nError address");
        exit(EXIT_FAILURE);
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_addr == NULL)
            continue;

        s=getnameinfo(ifa->ifa_addr,sizeof(struct sockaddr_in),host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
        
        /* argv[1] 
         if((strcmp(ifa->ifa_name,"eno1")==0)&&(ifa->ifa_addr->sa_family==AF_INET)) */
        if (argc < 2)
        {
	  printf("Usage:\n");
	  printf("\t%s interface_name\n", argv[0]);
	  printf("For example:\n");
	  printf("\t%s eth0\n", argv[0]);
          exit(1);
        }

        if((strcmp(ifa->ifa_name,argv[1])==0)&&(ifa->ifa_addr->sa_family==AF_INET))
        {
            if (s != 0)
            {
                printf("getnameinfo() failed: %s\n", gai_strerror(s));
                exit(EXIT_FAILURE);
            }
            /* printf("\tInterface : <%s>\n",ifa->ifa_name ); */
	    printf("%s\n", host);
        }
    }
    freeifaddrs(ifaddr);
    exit(EXIT_SUCCESS);
}
