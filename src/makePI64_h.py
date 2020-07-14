def map_num_to_int(num: int) -> int:
    return int((num - 48) * 25.5)


with open("./include/PI64", "r", encoding="utf-8") as afp:
    with open("./include/PI64.h", "w", encoding="utf-8") as bfp:
        bfp.write("#ifndef    _PI64_h\n")
        bfp.write("#define    _PI64_h\n\n")
        bfp.write("unsigned char PI64[7906][64] = {\n")

        line = list(afp.readline().strip())
        while len(line):
            bfp.write("    { ")

            line = [ord(pi) for pi in line]
            mapped = [map_num_to_int(pi) for pi in line]
            for pi in mapped:
                bfp.write(str(pi) + ", ")
            # for pi in line:
            #     bfp.write(str(ord(pi)) + ", ")

            bfp.write("},\n")
            line = list(afp.readline().strip())
        bfp.write("};\n\n")
        bfp.write("#endif //_PI64_h")
