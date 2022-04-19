#include "main.h"

/**
 * _printf - formatted output conversion and print data.
 * @format: input string.
 *
 * Return: number of chars printed.
 *

int _printf(const char *format, ...)
{
        unsigned int i = 0, len = 0, ibuf = 0;
        va_list arguments;
        int (*function)(va_list, char *, unsigned int);
        char *buffer;

        va_start(arguments, format), buffer = malloc(sizeof(char) * 1024);
        if (!format || !buffer || (format[i] == '%' && !format[i + 1]))
                return (-1);
        if (!format[i])
                return (0);
        for (i = 0; format && format[i]; i++)
        {
                if (format[i] == '%')
                {
                        if (format[i + 1] == '\0')
                        {       print_buf(buffer, ibuf), free(buffer), va_end(arguments);
                                return (-1);
                        }
                        else
                        {       function = get_print_func(format, i + 1);
                                if (function == NULL)
                                {
                                        if (format[i + 1] == ' ' && !format[i + 2])                                                return (-1);
                                        handl_buf(buffer, format[i], ibuf), len++, i--;
                                }
                                else
                                {
                                        len += function(arguments, buffer, ibuf);
                                        i += ev_print_func(format, i + 1);
                                }
                        } i++;
                }
                else
                        handl_buf(buffer, format[i], ibuf), len++;
                for (ibuf = len; ibuf > 1024; ibuf -= 1024)
                        ;
        }
        print_buf(buffer, ibuf), free(buffer), va_end(arguments);
        return (len);
}
*/


/**
 * _write - write to stdout
 * @output: the string to write
 */
void _write(buffer_t *output)
{
        write(1, output->start, output->len);
        free_buffer(output);
}

/**
 * _printf - produces output according to a format.
 * @format: is a character string.
 * Return: the length of the format.
 */
int _printf(const char *format, ...)
{
        unsigned int len = 0, i = 0;
        unsigned int (*convert)(va_list, buffer_t *);
        buffer_t *output;
        va_list args;

        output = init_buffer();
        if (output == NULL)
                return (-1);

        va_start(args, format);

        if (format == NULL)
                return (-1);

        while (*(format + i))
        {
                if (*(format + i) == '%')
                {
                        convert = handle_specifiers((format + i + 1));
                        if (convert != NULL)
                        {
                                len += convert(args, output);
                                format += 2;
                                continue;
                        }
                }
                len += _memcpy(output, (format + i), 1);
                i++;
        }

        _write(output);
        va_end(args);

        return (len);
}
