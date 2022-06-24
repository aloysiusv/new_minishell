/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 01:59:49 by lrandria          #+#    #+#             */
/*   Updated: 2021/06/10 19:37:29 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
// #include <bsd/string.h>
#include <stdlib.h>
#include <ctype.h>
#include "libft.h"

// void	test_ft_memset(void)
// {
// 	char	test[] = "almost every programmer should know memset!";
// 	char	user[] = "almost every programmer should know memset!";

// 	memset(test,'-',6);
// 	ft_memset(user,'-',6);
// 	printf("Expected: %s\n", test);
// 	printf("Result  : %s\n", user);
// }

// void	test_ft_bzero(void)
// {
// 	char	test[] = "almost every programmer should know memset!";
// 	char	user[] = "almost every programmer should know memset!";
	
// 	bzero(test, 6);
// 	ft_bzero(user, 6);
// 	if (memcmp(test, user, 44) == 0)
// 		printf("OK!\n");
// 	else
// 		printf("KO!\n");
// }

// void	test_ft_memcpy(void)
// {
// 	char	test[] = "almost every programmer should know memset!";
// 	char	user[] = "almost every programmer should know memset!";
// 	size_t	len = 3;
	
// 	memcpy(test, "Coucou", len);
// 	ft_memcpy(user, "Coucou", len);
// 	printf("Expected: %s\n", test);
// 	printf("Result  : %s\n", user);
// }

// void	test_ft_memccpy(void)
// {
// 	char	test[] = "almost every programmer should know memset!";
// 	char	user[] = "almost every programmer should know memset!";
// 	char	*ret;
// 	size_t	len = 26;
	
// 	ret = memccpy(test, "abcdefghijklmnopqrstuvwxyz", 'i', len);
// 	printf("%s\n", (ret == 0) ? "(null)" : ret);
// 	printf("Expected: %s\n", test);

// 	ret = ft_memccpy(user, "abcdefghijklmnopqrstuvwxyz", 'i', len);
// 	printf("%s\n", (ret == 0) ? "(null)" : ret);
// 	printf("Result  : %s\n", user);
// }

// void	test_ft_memmove(void)
// {
// 	char *str = NULL;
// 	memmove (str, str, 5);
// 	printf("%s\n", "(null)");
// char *str2 = NULL;
// ft_memmove(str2, str2, 5);
// printf("%s\n", "(null)");
// }

// void	test_ft_memchr(void)
// {
// 	char * pch;
// 	char str[] = "Example string";
// 	char		c = 'p';

// 	pch = (char*)memchr(str, c, strlen(str));
// 	printf("%s\n", (pch == 0) ? "(null)" : pch);
// 	pch = (char*)ft_memchr(str, c, strlen(str));
// 	printf("%s\n", (pch == 0) ? "(null)" : pch);
// }

// void	test_ft_memcmp(void)
// {
// 	char str1[15];
// 	char str2[15];
// 	int ret;

// 	memcpy(str1, "abcdef", 6);
// 	memcpy(str2, "ABCDEF", 6);
	
// 	ret = memcmp(str1, str2, 5);
// 	printf("%d\n", ret);
// 	ret = ft_memcmp(str1, str2, 5);
// 	printf("%d\n", ret);
// }

// void	test_ft_strlen(void)
// {
// 	char *s = "AMIRITE";
// 	printf("%ld\n", strlen(s));
// 	printf("%ld\n", ft_strlen(s));
// }

// void	test_ft_(int (*test)(int), int (*user)(int))
// {
// 	int		c = -1;
// 	int		flag = 0;
	
// 	while (++c < 256)
// 		if (!!test(c) != !!user(c))
// 		{
// 			printf("Error: %c, expected: %d, result: %d!\n", c, test(c), user(c));
// 			flag++;
// 		}
// 	if (flag == 0)
// 		printf("%s\n", "OK!");
// 	printf("================================================================\n");
// }

// void	test_ft_strchr(void)
// {
// 	char	str[] = "Hello World";
// 	char	c = 'l';
// 	char	*ret;

// 	ret = strchr(str, c);
// 	printf("%s\n", (ret == 0) ? "(null)" : ret);
// 	ret = ft_strchr(str, c);
// 	printf("%s\n", (ret == 0) ? "(null)" : ret);
// }

// void	test_ft_strrchr(void)
// {
// 	char	str[] = "Hello World";
// 	char	c = 'l';
// 	char	*ret;

// 	ret = strrchr(str, c);
// 	printf("%s\n", (ret == 0) ? "(null)" : ret);
// 	ret = ft_strrchr(str, c);
// 	printf("%s\n", (ret == 0) ? "(null)" : ret);
// }

// void	test_ft_strncmp(void)
// {
// 	char	s1[] = "aa";
// 	char	s2[] = "az";
// 	size_t	n = 1;
	
// 	printf("%d\n", strncmp(s1, s2, n));
// 	printf("%d\n", ft_strncmp(s1, s2, n));
// }

// void	test_ft_strlcpy(void)
// {
// 	char	test[40] = {0};
// 	char	user[40] = {0};

// 	for (int i = 0; i < 16; i++)
// 	{
// 		printf("%lu\n", strlcpy(test, "Hello G :)) ", i));
// 		printf("%s\n", test);
// 		printf("%lu\n", ft_strlcpy(user, "Hello G :))", i));
// 		printf("%s\n", user);
// 	}
// }

// void	test_ft_strlcat(void)
// {
// 	char	test[100];
// 	char	user[100];
// 	char	src[] = " world!";

// 	for (int i = 0; i < 16; i++)
// 	{
// 		memcpy(test, "Hello", 6);
// 		printf("%lu\n", strlcat(test, src, i));
// 		printf("%s\n", test);
// 		memcpy(user, "Hello", 6);
// 		printf("%lu\n", ft_strlcat(user, src, i));
// 		printf("%s\n", user);
// 		printf("=======================================\n");
// 	}
// }

// void	test_ft_strnstr(void)
// {
// 	char	big[]	= "Hello world!";
// 	char	little[] = "o wo";
// 	char	*ret;

// 	for (int i = 0; i <= 8; i++)
// 	{
// 		ret = strnstr(big, little, i);
// 		printf("len = %d: %s\n", i, (ret == 0) ? "(null)" : ret);
// 		ret = ft_strnstr(big, little, i);
// 		printf("len = %d: %s\n", i, (ret == 0) ? "(null)" : ret);
// 		printf("=======================================\n");
// 	} 
// }

// void	test_ft_atoi(void)
// {
// 	printf("%d\n", atoi("  ----684"));
// 	printf("%d\n", atoi("  -8684"));
// 	printf("%d\n", atoi(" 684"));
// 	printf("%d\n", ft_atoi("  ----684"));
// 	printf("%d\n", ft_atoi("  -8684"));
// 	printf("%d\n", ft_atoi(" 684"));
// }

// void	test_ft_calloc(void)
// {
// 	int	*tab_test;
// 	int	*tab_user;

// 	tab_test =(int *)calloc(10, sizeof(int));
// 	tab_user =(int *)ft_calloc(10, sizeof(int));
// 	printf("%d\n", memcmp(tab_test, tab_user, 10 * sizeof(int)));
// 	free(tab_test);
// 	free(tab_user);
// }

// void	test_ft_strdup(void)
// {
// 	char	*test;
// 	char	*user;

// 	printf("Expected: %s\n", test = strdup("youpi"));
// 	printf("Result  : %s\n", user = ft_strdup("youpi"));
// 	free(test);
// 	free(user);
// }

// void	test_ft_substr(void)
// {
// 	char	str[] = "coucou hinacaca";
// 	char	*ret;
// 	size_t	start = 0;
// 	size_t	how_much = 5;
	
// 	ret = ft_substr(str, start, how_much);
// 	printf("%s\n", ret);
// 	free (ret);
// }

// void	test_ft_strjoin(void)
// {
// 	char	pref[] = "hello";
// 	char	suff[] = "world";	
	
// 	printf("%s\n", ft_strjoin(pref, suff));
// }

// void	test_ft_strtrim(void)
// {
// 	char	s1[] = "";
// 	char	s2[] = "";
// 	char	*ret;
	
// 	ret = ft_strtrim(s1, "$_-");
// 	printf("Expected: %s\n", s2);
// 	printf("Result  : %s\n", (ret != 0) ? ret : "(null)");
// 	free(ret);
// }


// void	test_ft_itoa(void)
// {
// 	int		n[] = {-4, 0, 24, -1234567890, -2147483648, 2147483647};
// 	char	*ret;

// 	for (int i = 0; i < 6; i++)
// 	{
// 		ret = ft_itoa(n[i]);
// 		printf("%s\n", ret);
// 		free(ret);
// 	}
// }

// void	test_ft_split(void)
// {
// 	char    s[] = "+++hello+liana+ca++va+?+";
//     char    c = '+';
// 	char	**ret;

// 	ret = ft_split(s, c);
// 	for (int i = 0; ret[i]; i++)
// 	{
// 		printf("%s\n", ret[i]);
// 		free(ret[i]);
// 	}
// 	free (ret);
// }

// void	test_ft_lstclear(void)
// {
// 	t_list		*first = (t_list *)malloc(sizeof(t_list));
// 	t_list		*second = (t_list *)malloc(sizeof(t_list));
// 	t_list		*node;

// 	first->content = strdup("Hello World!");
// 	first->next = second;
// 	second->content = strdup("End game.");
// 	second->next = 0;

// 	node = first;
// 	while (node)
// 	{
// 		printf("%s\n", node->content);
// 		node = node->next;
// 	}
// 	ft_lstclear(&first, free);
// 	printf("%p\n", first);
// }

// int	main(void)
// {
	// test_ft_memset();
	// test_ft_bzero();
	// test_ft_memcpy();
	// test_ft_memccpy();
	// test_ft_memmove();
	// test_ft_memchr();
	// test_ft_memcmp();
	// test_ft_strlen();
	// test_ft_(isalpha, ft_isalpha);
	// test_ft_(isdigit, ft_isdigit);
	// test_ft_(isalnum, ft_isalnum);
	// test_ft_(isascii, ft_isascii);
	// test_ft_(isprint, ft_isprint);
	// test_ft_strchr();
	// test_ft_strrchr();
	// test_ft_strncmp();
	// test_ft_strlcpy();
	// test_ft_strlcat();
	// test_ft_strnstr();
	// test_ft_atoi();
	// test_ft_calloc();
	// test_ft_strdup();
	// test_ft_substr();
	// test_ft_strjoin();
	// test_ft_strtrim();
	// test_ft_itoa();
	// test_ft_split();
	// test_ft_lstclear();
// 	return (0);
// }