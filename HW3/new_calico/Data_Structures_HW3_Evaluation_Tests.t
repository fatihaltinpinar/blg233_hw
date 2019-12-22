- init:
    run: rm -f hw3
    blocker: true

- build:
    run: g++ -std=c++11 -Wall -Werror main.cpp -o hw3 # timeout: 4
    blocker: true


- case1:
    run: ./hw3 Network.txt Messages.txt
    points: 2
    script:
        - expect: "[ \r\n]*Traversing:0 5[ \r\n]*"                                                             # timeout: 2
        - expect: "[ \r\n]*Message:this is a message To:0 5 mh_13[ \r\n]*"                                                             # timeout: 2
        - expect: _EOF_ # timeout: 2
    return: 0

- case2:
    run: ./hw3 Network.txt Messages.txt
    points: 2
    script:
        - expect: "[ \r\n]*Traversing:0 5 2 7 9 12 6 16 3[ \r\n]*"                                                             # timeout: 2
        - expect: "[ \r\n]*Message:this is another message To:0 3 mh_8[ \r\n]*"                                                             # timeout: 2
        - expect: _EOF_ # timeout: 2
    return: 0

- case3:
    run: ./hw3 Network.txt Messages.txt
    points: 2
    script:
        - expect: "[ \r\n]*Traversing:0 5 2 7 9[ \r\n]*"                                                             # timeout: 2
        - expect: "[ \r\n]*Message:message3 To:0 9 mh_26[ \r\n]*"                                                             # timeout: 2
        - expect: _EOF_ # timeout: 2
    return: 0

- case4:
    run: ./hw3 Network.txt Messages.txt
    points: 2
    script:
        - expect: "[ \r\n]*Traversing:0 5 2 7 9 12 6 16 3[ \r\n]*"                                                             # timeout: 2
        - expect: "[ \r\n]*Can not be reached the mobile host mh_120 at the moment[ \r\n]*"                                                             # timeout: 2
        - expect: _EOF_ # timeout: 2
    return: 0

- case5:
    run: ./hw3 Network.txt Messages.txt
    points: 2
    script:
        - expect: "[ \r\n]*Traversing:0 5 2 7[ \r\n]*"                                                             # timeout: 2
        - expect: "[ \r\n]*Message:message5 To:0 5 7 mh_27[ \r\n]*"                                                             # timeout: 2
        - expect: _EOF_ # timeout: 2
    return: 0

- case6:
    run: ./hw3 Network.txt Messages.txt
    points: 2
    script:
        - expect: "[ \r\n]*Traversing:0 5 2 7 9 12 6[ \r\n]*"                                                             # timeout: 2
        - expect: "[ \r\n]*Message:message6 To:0 12 6 mh_6[ \r\n]*"                                                             # timeout: 2
        - expect: _EOF_ # timeout: 2
    return: 0

- 2case1:
    run: ./hw3 Network2.txt Messages2.txt
    points: 2
    script:
        - expect: "[ \r\n]*Traversing:0 1[ \r\n]*"                                                             # timeout: 2
        - expect: "[ \r\n]*Message:cant_make_dick_jokes_since_i_will_commit_this To:0 1 mh_3[ \r\n]*"                                                             # timeout: 2
        - expect: _EOF_ # timeout: 2
    return: 0

- 2case2:
    run: ./hw3 Network2.txt Messages2.txt
    points: 2
    script:
        - expect: "[ \r\n]*Traversing:0 1[ \r\n]*"                                                             # timeout: 2
        - expect: "[ \r\n]*Message:bir To:0 1 mh_1[ \r\n]*"                                                             # timeout: 2
        - expect: _EOF_ # timeout: 2
    return: 0

- 2case3:
    run: ./hw3 Network2.txt Messages2.txt
    points: 2
    script:
        - expect: "[ \r\n]*Traversing:0 1[ \r\n]*"                                                             # timeout: 2
        - expect: "[ \r\n]*Message:iki To:0 1 mh_2[ \r\n]*"                                                             # timeout: 2
        - expect: _EOF_ # timeout: 2
    return: 0

- 2case4:
    run: ./hw3 Network2.txt Messages2.txt
    points: 2
    script:
        - expect: "[ \r\n]*Traversing:0 1[ \r\n]*"                                                             # timeout: 2
        - expect: "[ \r\n]*Can not be reached the mobile host mh_5 at the moment[ \r\n]*"                                                             # timeout: 2
        - expect: _EOF_ # timeout: 2
    return: 0

- 3case1:
    run: ./hw3 Network3.txt Messages3.txt
    points: 2
    script:
        - expect: "[ \r\n]*Traversing:0 1 2[ \r\n]*"                                                             # timeout: 2
        - expect: "[ \r\n]*Message:bir To:0 1 2 mh_1[ \r\n]*"                                                             # timeout: 2
        - expect: _EOF_ # timeout: 2
    return: 0

- 3case2:
    run: ./hw3 Network3.txt Messages3.txt
    points: 2
    script:
        - expect: "[ \r\n]*Traversing:0 1 2 3 4 5[ \r\n]*"                                                             # timeout: 2
        - expect: "[ \r\n]*Message:bes To:0 5 mh_5[ \r\n]*"                                                             # timeout: 2
        - expect: _EOF_ # timeout: 2
    return: 0

- 3case3:
    run: ./hw3 Network3.txt Messages3.txt
    points: 2
    script:
        - expect: "[ \r\n]*Traversing:0 1 2 3[ \r\n]*"                                                             # timeout: 2
        - expect: "[ \r\n]*Message:uc To:0 3 mh_3[ \r\n]*"                                                             # timeout: 2
        - expect: _EOF_ # timeout: 2
    return: 0

- 3case4:
    run: ./hw3 Network3.txt Messages3.txt
    points: 2
    script:
        - expect: "[ \r\n]*Traversing:0 1 2 3[ \r\n]*"                                                             # timeout: 2
        - expect: "[ \r\n]*Message:dort To:0 3 mh_4[ \r\n]*"                                                             # timeout: 2
        - expect: _EOF_ # timeout: 2
    return: 0

- 3case5:
    run: ./hw3 Network3.txt Messages3.txt
    points: 2
    script:
        - expect: "[ \r\n]*Traversing:0 1 2 3 4 5[ \r\n]*"                                                             # timeout: 2
        - expect: "[ \r\n]*Can not be reached the mobile host mh_6 at the moment[ \r\n]*"                                                             # timeout: 2
        - expect: _EOF_ # timeout: 2
    return: 0

- 3case6:
    run: ./hw3 Network3.txt Messages3.txt
    points: 1
    script:
        - expect: "[ \r\n]*Traversing:0 1 2 3 4 5[ \r\n]*"                                                             # timeout: 2
        - expect: "[ \r\n]*Can not be reached the mobile host mh_2134 at the moment[ \r\n]*"                                                             # timeout: 2
        - expect: _EOF_ # timeout: 2
    return: 0