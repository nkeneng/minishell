

// function that exchanges a substring within a string
// from is the index of the first char of the substring to exchange
// to is the index of the last char of the substring to exchange
// exch_with is the string that should be exchanged with the substring
// returns the new string
char	*ft_exchange_within(char *original, int from, int to, char *exch_with)
{
	char	*new;

	new = malloc(sizeof(char) * (ft_strlen(original) + ft_strlen(exch_with) - (to - from)));
	if (!new)
		return (NULL);
	ft_strlcpy(new, original, from + 1);
	ft_strlcat(new, exch_with, from + ft_strlen(exch_with) + 1);
	ft_strlcat(new, original + to + 1, ft_strlen(original) - to + 1);
	return (new);
}
