
#include "../../includes/minishell.h"

// function removes beginning and ending quotes from word
// param: word_desc with flag W_SQUOTED or W_DQUOTED
// returns word_desc
t_word_desc	*remove_quotes(t_word_desc *word)
{
	int		len;
	char	*end_string;
	int		len_end;

	if (!(word->flags & W_SQUOTED || word->flags & W_DQUOTED))
		return (word);
	len = ft_strlen(word->word);
	end_string = ft_strrchr(word->word, word->word[0]);
	// while (word->word[len - 1] != word->word[0])
	// 	len--;
	// word->word[len - 1] = '\0';
	len_end = ft_strlen(end_string);
	ft_bzero(end_string, len_end);
	end_string[0] = '\0';
	ft_memmove(word->word, word->word + 1, len - len_end);
	return (word);
}

#include <stdio.h>
#include <string.h>

int main() {
    t_word_desc word1;
    t_word_desc word2;
    // Initialize word1 with single quotes
    word1.word = ft_strdup("'hello'  ");
    word1.flags = W_SQUOTED;

    // Initialize word2 with double quotes
	word2.word = ft_strdup("\"world\" 	  ");
    word2.flags = W_DQUOTED;

    // Remove quotes
    remove_quotes(&word1);
    remove_quotes(&word2);

    // Print results
    printf("Word1 after removing quotes: %s\n", word1.word);
    printf("Word2 after removing quotes: %s\n", word2.word);

	free(word1.word);
	free(word2.word);
    return 0;
}

