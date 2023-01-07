#include "os_file.h"

#include <cstdio>


int main()
{
    int TOTAL_SIZE = 1000;
    char* current_directory = (char*)calloc(128, sizeof(char));
    file_manager_t fm;
    setup_file_manager(&fm);

    printf("create(TOTAL_SIZE) %d\n",fm.create(TOTAL_SIZE));
    printf("create_dir(\"dir1\") %d\n",fm.create_dir("dir1"));
    printf("create_dir(\"dir1/dir11\") %d\n",fm.create_dir("dir1/dir11"));
    printf("change_dir(\"dir1\") %d\n",fm.change_dir("dir1"));
    printf("create_dir(\"../dir2\") %d\n",fm.create_dir("../dir2"));
    printf("create_dir(\"../dir2/dir3\") %d\n",fm.create_dir("../dir2/dir3"));
    printf("remove(\"/dir2/dir3\", 0) %d\n",fm.remove("/dir2/dir3", 0));
    printf("create_dir(\"/dir3/dir31\") %d\n",fm.create_dir("/dir3/dir31"));
    printf("create_dir(\"../dir3/dir31\") %d\n",fm.create_dir("../dir3/dir31"));
    printf("create_dir(\"../dir2\") %d\n",fm.create_dir("../dir2"));
    printf("create_file(\"/dir2/file1\", 1) %d\n",fm.create_file("/dir2/file1", 1));
    printf("create_dir(\"/dir2/dir21\") %d\n",fm.create_dir("/dir2/dir21"));
    printf("create_dir(\"/dir2/file1\") %d\n",fm.create_dir("/dir2/file1"));
    printf("create_dir(\"../dir2/file1\") %d\n",fm.create_dir("../dir2/file1"));
    printf("create_dir(\"../dir2/file1/dir\") %d\n",fm.create_dir("../dir2/file1/dir"));
    printf("create_dir(\"../dir2/dir22\") %d\n",fm.create_dir("../dir2/dir22"));
    printf("change_dir(\"dir2\") %d\n",fm.change_dir("dir2"));
    printf("change_dir(\"dir11\") %d\n",fm.change_dir("dir11"));
    printf("remove(\"../../dir2/file1\", 0) %d\n",fm.remove("../../dir2/file1", 0));
    printf("create_dir(\"../../dir2/file1\") %d\n",fm.create_dir("../../dir2/file1"));
    printf("remove(\"../../dir2/file1\", 0) %d\n",fm.remove("../../dir2/file1", 0));
    printf("create_file(\"../../dir2/file1\", 1) %d\n",fm.create_file("../../dir2/file1", 1));
    printf("change_dir(\".\") %d\n",fm.change_dir("."));
    printf("change_dir(\"/dir1/dir11\") %d\n",fm.change_dir("/dir1/dir11"));
    printf("change_dir(\"/dir1/dir11/dir3\") %d\n",fm.change_dir("/dir1/dir11/dir3"));
    printf("change_dir(\"/dir1\") %d\n",fm.change_dir("/dir1"));
    printf("change_dir(\"./dir11\") %d\n",fm.change_dir("./dir11"));
    printf("change_dir(\"..\") %d\n",fm.change_dir(".."));
    printf("create_file(\"./dir11/file.txt\", 1) %d\n",fm.create_file("./dir11/file.txt", 1));
    printf("remove(\"dir11\", 0) %d\n",fm.remove("dir11", 0));
    printf("remove(\"./dir11\", 0) %d\n",fm.remove("./dir11", 0));
    printf("remove(\"./dir11\", 1) %d\n",fm.remove("./dir11", 1));
    printf("list(\"..\",0) %d\n",fm.list("..",0));
    printf("list(\"dir1\",0) %d\n",fm.list("dir1",0));
    printf("list(\".\",0) = %d\n", fm.list(".",0));
    printf("list(\"./dir11/file.txt\",0) %d\n", fm.list("./dir11/file.txt",0));
    printf("\n", fm.create_file("file11.txt",1));
    printf("list(\"./file11.txt\",0) %d\n", fm.list("./file11.txt",0));
    printf("list(\"file11.txt\",0) %d\n", fm.list("file11.txt",0));
    printf("create_file(\"../dir2/a_file22.txt\",1) %d\n", fm.create_file("../dir2/a_file22.txt",1));
    printf("list(\"../dir2\",0) %d\n", fm.list("../dir2",0));
    printf("list(\"../dir2\",1) %d\n", fm.list("../dir2",1));
    printf("list(\"../dir1 ../dir2\",1) %d\n", fm.list("../dir1 ../dir2",1));
    printf("list(\"../dir2 ../dir3\",1) %d\n", fm.list("../dir2 ../dir3",1));
/*
 ТЕСТ 2 с КОНТЕСТА
    printf("create(1000) = %d\n", fm.create(1000));
    printf("create_dir(\"dir1\") %d\n",fm.create_dir("dir1"));
    printf("create_dir(\"dir1/dir11\") %d\n",fm.create_dir("dir1/dir11"));
    printf("change_dir(\"dir1\") %d\n",fm.change_dir("dir1"));
    printf("create_dir(\"../dir2\") %d\n",fm.create_dir("../dir2"));
    printf("create_dir(\"../dir2/dir3\") %d\n",fm.create_dir("../dir2/dir3"));
    printf("remove(\"/dir2/dir3\", 0) %d\n",fm.remove("/dir2/dir3", 0));
    printf("create_dir(\"/dir3/dir31\") %d\n",fm.create_dir("/dir3/dir31"));
    printf("create_dir(\"../dir3/dir31\") %d\n",fm.create_dir("../dir3/dir31"));
    printf("create_dir(\"../dir2\") %d\n",fm.create_dir("../dir2"));
    printf("create_file(\"/dir2/file1\", 1) %d\n",fm.create_file("/dir2/file1", 1));
    printf("create_dir(\"/dir2/dir21\") %d\n",fm.create_dir("/dir2/dir21"));
    printf("create_dir(\"/dir2/file1\") %d\n",fm.create_dir("/dir2/file1"));
    printf("create_dir(\"../dir2/file1\") %d\n",fm.create_dir("../dir2/file1"));
    printf("create_dir(\"../dir2/file1/dir\") %d\n",fm.create_dir("../dir2/file1/dir"));
    printf("create_dir(\"../dir2/dir22\") %d\n",fm.create_dir("../dir2/dir22"));
    printf("list(\"/dir1 /dir2\", 1) = %d\n", fm.list("/dir1 /dir2", 1));
    printf("create_dir(\"..\") %d\n",fm.create_dir(".."));
    printf("create_dir(\"../dir2/.\") %d\n",fm.create_dir("../dir2/."));
    printf("change_dir(\"dir2\") %d\n",fm.change_dir("dir2"));
    printf("change_dir(\"dir11\") %d\n",fm.change_dir("dir11"));
    printf("remove(\"../../dir2/file1\", 0) %d\n",fm.remove("../../dir2/file1", 0));
    printf("create_dir(\"../../dir2/file1\") %d\n",fm.create_dir("../../dir2/file1"));
    printf("remove(\"../../dir2/file1\", 0) %d\n",fm.remove("../../dir2/file1", 0));
    printf("change_dir(\".\") %d\n",fm.change_dir("."));
    printf("change_dir(\"/dir1/dir11\") %d\n",fm.change_dir("/dir1/dir11"));
    printf("change_dir(\"/dir1/dir11/dir3\") %d\n",fm.change_dir("/dir1/dir11/dir3"));

 */
/*
    printf("create(TOTAL_SIZE) %d\n",fm.create(TOTAL_SIZE));
    printf("create_dir(\"/dir1\") = %d\n", fm.create_dir("/dir1"));
    printf("create_dir(\"/dir1/dir2\") = %d\n", fm.create_dir("/dir1/dir2"));
    printf("change_dir(\"/dir1/dir2\") = %d\n", fm.change_dir("/dir1/dir2"));
    printf("create_dir(\"/dir11\") = %d\n", fm.create_dir("/dir11"));
    printf("create_dir(\"/dir11/dir13\") = %d\n", fm.create_dir("/dir11/dir13"));
    printf("create_dir(\"/dir12\") = %d\n", fm.create_dir("/dir12"));
    printf("create_dir(\"/dir12/dir14\") = %d\n", fm.create_dir("/dir12/dir14"));
    printf("change_dir(\"../..\") = %d\n", fm.change_dir("../.."));

    printf("create_file(\"file2\", 16) = %d\n", fm.create_file("file2", 16));
    printf("create_file(\"file1\", 8) = %d\n", fm.create_file("file1", 8));

    fm.get_cur_dir(current_directory);
    printf("Current directory = %s\n\n", current_directory);

    printf("change_dir(\"/dir1/dir2\") = %d\n\n", fm.change_dir("/dir1/dir2"));

    fm.get_cur_dir(current_directory);
    printf("Current directory = %s\n\n", current_directory);


    printf("create_dir(\"/dir1/dir2/dir3\") = %d\n", fm.create_dir("/dir1/dir2/dir3"));
    printf("create_file(\"/dir1/dir2/dir3/file4\") = %d\n", fm.create_file("/dir1/dir2/dir3/file4", 8));

    printf("create_file(\"/dir1/dir2/dir3/file5\") = %d\n", fm.create_file("/dir1/dir2/dir3/file5", 12));

    printf("create_file(\"/dir1/../dir8\") = %d\n", fm.create_dir("/dir1/../dir8"));

    printf("create_file(\"/dir1/dir2/file6\") = %d\n", fm.create_file("/dir1/dir2/file6", 12));
    printf("create_dir(\"/dir1/dir2/dir7\") = %d\n", fm.create_dir("/dir1/dir2/dir7"));


    printf("create_file(\"../file9\") = %d\n", fm.create_file("../file9", 10));

    printf("remove(\"/dir1/dir2/dir3/file4\", 0) = %d\n", fm.remove("/dir1/dir2/dir3/file4", 0));
    printf("remove(\"/dir1/dir2/dir3/file5\", 0) = %d\n", fm.remove("/dir1/dir2/dir3/file5", 0));

    printf("\nlist(\"/dir1 /dir1/dir2 /file1\", 1) = %d\n", fm.list("/dir1 /dir1/dir2 /file1", 1));
*/

    printf("destroy = %d\n", fm.destroy());    
    
    free(current_directory);

    return 0;
}
