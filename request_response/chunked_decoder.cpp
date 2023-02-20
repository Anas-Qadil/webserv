/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunked_decoder.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:51:15 by aqadil            #+#    #+#             */
/*   Updated: 2023/02/21 00:43:27 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "request_response.hpp"

static	long int	ft_len(long n)
{
	int	i;

	i = 0;
	if (n <= 0)
	{
		n = n * -1 ;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int			len;
	char		*b;
	long		l;

	l = n;
	len = ft_len(l);
	b = (char *)malloc((len + 1) * sizeof(char));
	if (!b)
		return (NULL);
	b[len--] = '\0';
	if (l == 0)
		b[0] = '0';
	if (l < 0)
	{
		b[0] = '-';
		l = l * -1;
	}
	while (l > 0)
	{
		b[len--] = (l % 10) + 48;
		l = l / 10;
	}
	return (b);
}

std::string chunked_decoder(std::string content) {
	size_t  pos;
	size_t  len;
	std::string res;

	len = content.npos;
	for (; content.length();) {
		pos = content.find(CRLF);
		if (pos == content.npos)
			break ;
		else if (!pos)
			content.erase(0, 2);
		else if (pos) {
            len = std::stoul(content.substr(0, pos), NULL, 16);
			if (len > content.length())
				break ;
			res += content.substr(pos + 2, len);
			content = content.substr(pos + 2 + len + 2, content.length() - pos - 2 - len - 2);
		}
		else {
			content = content.substr(2, content.length() - 2);
		}
	}
	return res;
}