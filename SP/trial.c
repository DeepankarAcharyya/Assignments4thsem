        if (e == 1 && Immediate == 0)
        {
            fprintf(machine_code_file, "%.5x\n", add);
        }
        else if (e == 1 && Immediate != 0)
        {
            int q = 5 - strlen(str);
            while (q > 0)
            {
                fprintf(machine_code_file, "%x", 0);
                q--;
            }
            fprintf(machine_code_file, "%s\n", str);
        }
        else if ( e == 0 && Immediate == 0)
        {
            fprintf(machine_code_file, "%.3x\n", add % 0x1000);
        }
        else if ( e == 0 && Immediate != 0)
        {
            int q = 3 - strlen(str);
            while (q > 0)
            {
                fprintf(machine_code_file, "%x", 0);
                q--;
            }
            fprintf(machine_code_file, "%s\n", str);
        }