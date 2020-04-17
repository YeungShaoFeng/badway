with open("./include/PI64", "r", encoding="utf-8") as afp:
    with open("./PI64.h", "w", encoding="utf-8") as bfp:
        bfp.write("#ifndef    PI64_h\n")
        bfp.write("#define    PI64_h    1\n\n")
        bfp.write("char PI64[7906][64] = {\n")

        line = list(afp.readline().strip())
        while len(line):
            bfp.write("{ ")

            for pi in line:
                bfp.write(str(ord(pi) - 48) + ", ")

            bfp.write("},\n")
            line = list(afp.readline().strip())
        bfp.write("};\n")
        bfp.write("#endif //PI64_h")
