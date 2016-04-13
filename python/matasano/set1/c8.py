from matasano.util.converters import hex_to_bytestr

if __name__ == "__main__":

    chal_file = open("matasano/data/c8.txt", 'r');

    coll_count = {}
    for idx, line in enumerate(chal_file):
        count = 0
        ct = line[:-1]
        for i in range(0, len(ct), 32):
            for j in range(i+32, len(ct), 32):
                if ct[i:i+32] == ct[j:j+32]:
                    print("Block collision found in ciphertext: {} Block {} == Block {}".format(idx, i//16, j//16))
                    count += 1
        coll_count[idx] = count


    most_coll = max(coll_count, key=coll_count.get)
    print("Ciphertext {} had the most collisions with {}".format(most_coll, coll_count[most_coll]))

