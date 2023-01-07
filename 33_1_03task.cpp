#include <cstring>
#include "os_file.h"
#include <cstdio>
#include <cstdlib>


int times = 0;
int node = 0;
int exist = 0;
int incorrect_path = 0;
int common_size = 0;

struct Element {
    int size;
    int ch_amount;
    char name[33];
    struct Element** child;
    struct Element* parent;

};
typedef struct Element Node;

Node* root = NULL;
Node* cur_dir = NULL;

int create(int disk_size)
{


    if (exist == 0 && disk_size > 0)
    {
        common_size = disk_size;

        root = (Node*)malloc(sizeof(Node));

        if (root != NULL)
        {
            exist = 1;
            strcpy(root->name, "/");
            root->child = NULL;
            root->parent = NULL;
            root->ch_amount = 0;
            root->size = 0;
            cur_dir = root;

            return 1;
        }
        else
        {

            return 0;
        }
    }
    else
    {
        //       exist = 2;
        return 0;
    }
}


void cut(char* name, char* path, int* num, int path_length)
{

    int cur = 0;

    while ((path[*num] != '/') && (*num < path_length))
        name[cur++] = path[(*num)++];

    if (path[*num] == '/')
        (*num)++;

    name[cur] = '\0';

}
char* move_tree(char* path, Node** dir, int path_length, char* check_dir)
{ 

    char* tmp_dir = (char*)calloc(33, sizeof(char));
    
    int num = 0;

    if (path[0] == '/')
    {
        *dir = root;
        num++;
    }
    else
    {
        *dir = cur_dir;
        num = 0;
    }

    while (num < path_length)
    {
        cut(tmp_dir, path, &num, path_length);

        if (strcmp(tmp_dir, ".") == 0)
            continue;
        else if (strcmp(tmp_dir, "..") == 0)
            if (*dir == root)
            {
                *dir = NULL;
                break;
            }
            else
                *dir = (*dir)->parent;
        else
        {
            if (((*dir)->size) == 0)
            {
                for (int i = 0; i < (*dir)->ch_amount; i++)
                {
                    if (strcmp((*dir)->child[i]->name, tmp_dir) == 0)
                    {
                        strcpy(check_dir, (*dir)->child[i]->name);
                        if (times == 1)
                        {
                            times++;
                            break;
                        }
                        (*dir) = (*dir)->child[i];
                        node = i;
                        break;
                    }
                    else
                    {
                        incorrect_path++;
                        if (incorrect_path == (*dir)->ch_amount)
                        {
                            times++;
                            incorrect_path = 0;
                        }
                    }

                }

            }
            else
            {
                (*dir) = NULL;
                break;
            }
        }
        incorrect_path = 0;
    }
    if(tmp_dir != NULL)
        free(tmp_dir);
        
    return check_dir;
}
void move_tree_create(char* path, Node** dir, int path_length)
{

    char* tmp_dir = (char*)calloc(33, sizeof(char));
    int num = 0;
    int flag = 0;

    if (path[0] == '/')
    {
        *dir = root;
        num++;
    }
    else
    {
        *dir = cur_dir;
        num = 0;
    }

    while (num < path_length)
    {
        cut(tmp_dir, path, &num, path_length);

        if (strcmp(tmp_dir, ".") == 0)
            continue;
        else if (strcmp(tmp_dir, "..") == 0)
            if (*dir == root)
            {
                *dir = NULL;
                break;
            }
            else
                *dir = (*dir)->parent;
        else
        {
            if (((*dir)->size) == 0)
            {
                for (int i = 0; i < (*dir)->ch_amount; i++)
                {
                    flag = 1;
                    if (strcmp((*dir)->child[i]->name, tmp_dir) == 0)
                    {
                        if (times == 1)
                        {
                            times++;
                            break;
                        }
                        (*dir) = (*dir)->child[i];
                        node = i;
                        break;
                    }
                    else
                    {
                        incorrect_path++;
                        if (incorrect_path == (*dir)->ch_amount)
                        {
                            times++;
                            incorrect_path = 0;
                        }
                    }

                }
                if(((*dir) -> ch_amount == 0) && strlen(tmp_dir) != 0 && flag == 0)
                    times = 1;

                flag = 0;
            }
            else
            {
                (*dir) = NULL;
                break;
            }
        }
        incorrect_path = 0;
    }
    if(tmp_dir != NULL)
        free(tmp_dir);
}


int create_node(const char* path, int size_f = 0)
{
    if(size_f > common_size)
        return 0;

    int path_length = (int)strlen(path);
    int num = 0;
    char* tmp_path = (char*)calloc((path_length + 1), sizeof(char));
    char* path_dir = (char*)calloc(33, sizeof(char));
    char* check_dir = (char*)calloc(33, sizeof(char));
    Node* tmp;

    strcpy(tmp_path, path);

    while (num < path_length)
    {
        strcpy(path_dir, "");
        cut(path_dir, tmp_path, &num, path_length);
    }

  //  strcat(tmp_path, "/");
    check_dir = move_tree(tmp_path, &tmp, path_length, check_dir);

    if (tmp == NULL || times >= 2)
    {
        times = 0;
        incorrect_path = 0;
        if(check_dir != NULL)
            free(check_dir);
        if(path_dir != NULL)
            free(path_dir);
        if(tmp_path != NULL)
            free(tmp_path);
        return 0;
    }
    times = 0;
    incorrect_path = 0;

    if (strcmp(check_dir, path_dir) == 0)
    {
        if(check_dir != NULL)
            free(check_dir);
        if(path_dir != NULL)
            free(path_dir);
        if(tmp_path != NULL)
            free(tmp_path);
        return 0;
    }
    if(check_dir != NULL)
        free(check_dir);

    if((strcmp(path_dir, ".") == 0) || (strcmp(path_dir, "..") == 0))
    {
        if(tmp_path != NULL)
            free(tmp_path);
        if(path_dir != NULL)
            free(path_dir);
        return 0;
    }
    if (tmp->ch_amount > 0)
    {
        tmp->child = (Node**)realloc(tmp->child, sizeof(Node*) * (tmp->ch_amount + 1));

        tmp->child[tmp->ch_amount] = (Node*)malloc(sizeof(Node));


        strcpy(tmp->child[tmp->ch_amount]->name, path_dir);
        tmp->child[tmp->ch_amount]->child = NULL;
        tmp->child[tmp->ch_amount]->size = size_f;
        tmp->child[tmp->ch_amount]->ch_amount = 0;
        tmp->child[tmp->ch_amount]->parent = tmp;

        common_size -= size_f;
       // printf("%s \n", tmp->child[tmp->ch_amount]->name);
        tmp->ch_amount++;

        
        if(tmp_path != NULL)
            free(tmp_path);
        if(path_dir != NULL)
            free(path_dir);
        
        

        return 1;
    }
    else
    {
        tmp->child = (Node**)malloc(sizeof(Node*));
        tmp->child[0] = (Node*)malloc(sizeof(Node));


        strcpy(tmp->child[0]->name, path_dir);
        tmp->child[0]->child = NULL;
        tmp->child[0]->size = size_f;
        tmp->child[0]->ch_amount = 0;
        tmp->child[0]->parent = tmp;

        common_size -= size_f;
        //printf("%s \n", tmp->child[0]->name);
        tmp->ch_amount++;

        
        if(tmp_path != NULL)
            free(tmp_path);
        if(path_dir != NULL)
            free(path_dir);
      
            
        return 1;
    }

}

int change_dir(const char* path)
{
    int num = 0;
    int path_length = (int)strlen(path);
    char* tmp_path = (char*)calloc((path_length + 1), sizeof(char));
    char* check_dir = (char*)calloc(33, sizeof(char));
    char* path_dir = (char*)calloc(33, sizeof(char));
    strcpy(tmp_path, path);
    Node* tmp;

    if (exist == 1)
    {
        while (num < path_length)
        {
            strcpy(path_dir, "");
            cut(path_dir, tmp_path, &num, path_length);
        }

        check_dir = move_tree(tmp_path, &tmp, path_length, check_dir);

        if (strcmp(check_dir, path_dir) != 0 && strcmp(check_dir, "") != 0)
        {
            times = 0;
            incorrect_path = 0;
            if(check_dir != NULL)
                free(check_dir);
            if(path_dir != NULL)
                free(path_dir);
            if(tmp_path != NULL)
                free(tmp_path);
            return 0;
        }

        if (times != 0)
        {
            incorrect_path = 0;
            times = 0;
            if(tmp_path != NULL)
              free(tmp_path);
            return 0;
        }

        incorrect_path = 0;
        cur_dir = tmp;
        if(tmp_path != NULL)
              free(tmp_path);
        //printf("%s \n", cur_dir->name);

        return 1;
    }
    else
    {
        if(tmp_path != NULL)
              free(tmp_path);
        return 0;
    }
}

void get_cur_dir(char* dst)
{
    strcpy(dst, "");
    if (strcmp(cur_dir->name, "/") != 0)
    {

        Node* tmp = NULL;
        tmp = cur_dir;
        int size = 20, amount = 0, common_length = 0;
        char** tmp_path = (char**)malloc(size * sizeof(char*));
        int* length = (int*)malloc(size * sizeof(int));

        while (tmp->parent != NULL)
        {
            if (amount < 21)
            {
                length[amount] = strlen(tmp->name);
                length[amount]++;
                tmp_path[amount] = (char*)calloc((length[amount] + 1), sizeof(char));
                strcat(tmp_path[amount], "/");
                strcat(tmp_path[amount], tmp->name);
                tmp = tmp->parent;

                common_length += length[amount];
                amount++;
            }
            else
            {
                tmp_path = (char**)realloc(tmp_path, size + 1);
                length = (int*)realloc(length, size + 1);
                size++;

                length[amount] = strlen(tmp->name);
                length[amount]++;
                tmp_path[amount] = (char*)calloc((length[amount] + 1), sizeof(char));
                strcat(tmp_path[amount], "/");
                strcat(tmp_path[amount], tmp->name);
                tmp = tmp->parent;

                common_length += length[amount];
                amount++;
            }
        }

        char* tmp_dir = (char*)calloc((common_length + 1), sizeof(char));

        for (int i = amount - 1; i >= 0; i--)
        {
            strcat(tmp_dir, tmp_path[i]);
        }

                for (int i = 0; i < amount; i ++)
                {
                    free(tmp_path[i]);
                }

              free(tmp_path);
        
        strcat(dst, tmp_dir);
        free(tmp_dir);
        free(length);
    }
    else
    {
        strcpy(dst, "/");
    }

}
int remove(const char* path, int recursive)
{
    Node* tmp;
    Node* tmp_cur_dir;
    int ch_amount;
    tmp_cur_dir = cur_dir;

    int ret_res = 1;

    if (exist == 1)
    {
        int path_length = (int)strlen(path);
        int num = 0;
        char* path_dir = (char*)calloc(33, sizeof(char));
        char* tmp_path = (char*)calloc((path_length + 1), sizeof(char));

        strcpy(tmp_path, path);

        while (num < path_length)
        {
            strcpy(path_dir, "");
            cut(path_dir, tmp_path, &num, path_length);
        }

        move_tree_create(tmp_path, &tmp, path_length);

        if(strcmp(tmp->name, path_dir) != 0)
        {
            if(path_dir != NULL)
              free(path_dir);
            if(tmp_path != NULL)
              free(tmp_path);
            return 0;
        }
        if (times != 0)
        {
            incorrect_path = 0;
            times = 0;
            if(path_dir != NULL)
              free(path_dir);
            if(tmp_path != NULL)
              free(tmp_path);
            
            return 0;
        }
        incorrect_path = 0;
        if(tmp_path != NULL)
            free(tmp_path);
        if(path_dir != NULL)
            free(path_dir);
            
        if ((tmp->size != 0) || (tmp->ch_amount == 0))
        {
            tmp = tmp->parent;

            if (strcmp(tmp->child[node]->name, cur_dir->name) != 0)
            {

                common_size += tmp->child[node]->size;
                free(tmp->child[node]);

                tmp->ch_amount--;

                for (int i = node; i < tmp->ch_amount; i++)
                    tmp->child[i] = tmp->child[i + 1];

                tmp->child = (Node**)realloc(tmp->child, sizeof(Node*) * tmp->ch_amount);
            }
            else
            {
                cur_dir = root;

                free(tmp->child[node]);

                tmp->ch_amount--;

                for (int i = node; i < tmp->ch_amount; i++)
                    tmp->child[i] = tmp->child[i + 1];

                tmp->child = (Node**)realloc(tmp->child, sizeof(Node*) * tmp->ch_amount);
            }
        }
        else
        {
            if (recursive == 1)
            {
                cur_dir = tmp;

                ch_amount = tmp->ch_amount;

                for (int i = 0; i < ch_amount; ch_amount--)
                    ret_res = remove(tmp->child[i]->name, 1);

                cur_dir = tmp_cur_dir;

                ret_res = remove(path, 0);
                
            }
            else
            {
                return 0;
            }
        }
    }
    else
        return 0;

    
    return ret_res;

}
int destroy()
{
    if (exist == 1)
    {
        if (root->ch_amount != 0)
        {
            Node* tmp = root;
            Node* tmp_cur_dir = cur_dir;
            int ch_amount, ret_res;

            cur_dir = tmp;

            ch_amount = tmp->ch_amount;

            for (int i = 0; i < ch_amount; ch_amount--)
                ret_res = remove(tmp->child[i]->name, 1);

            cur_dir = tmp_cur_dir;
        }

        free(root);
        exist = 0;
        return 1;
    }
    else
        return 0;
}
int cut_list(char* name, char* path, int* num, int path_length)
{

    int cur = 0;
    char slash = 32;

    while (((*num) < path_length) && (path[(*num)] != slash))
        name[cur++] = path[(*num)++];

    if (path[*num] == '/' || path[*num] == slash)
        (*num)++;

    name[cur] = '\0';

    cur++;

    return cur;
}
int cmp(void const* l, void const* r)
{
    return strcmp(*(char**)l, *(char**)r);
}

void sort_dir(char** tmp_path, int size)
{
    qsort(tmp_path, size, sizeof(char*), cmp);
}
void sort_file(char** tmp_path, int size)
{
    qsort(tmp_path, size, sizeof(char*), cmp);
}
char *add_path(const char * path, char* new_path)
{
    char *tmp_path = (char*)calloc(128, sizeof(char));

    get_cur_dir(tmp_path);

    int new_length, tmp_length = (int)strlen(tmp_path), path_length = (int)strlen(path);

    new_length = tmp_length + path_length + 2;

    new_path = (char*)calloc(new_length, sizeof(char));

    strcpy(new_path, tmp_path);
    if(strcmp(tmp_path, "/") != 0)
        strcat(new_path, "/");

    strcat(new_path, path);

    free(tmp_path);

    return new_path;
}
int list(const char* path, int dir_first)
{
    int ret_res = 0, num = 0, new_length = 0, files = 0, dirs = 0, ch_amount = 0, path_length = (int)strlen(path);

    char* path_dir = (char*)calloc(128, sizeof(char));
    char* tmp_dir = (char*)calloc((path_length + 1), sizeof(char));
    char* copy_path = (char*)calloc(128, sizeof(char));
    Node* tmp;

    strcpy(tmp_dir, path);

    while(num < path_length)
    {
        new_length = cut_list(path_dir, tmp_dir, &num, path_length);
        strcpy(copy_path, path_dir);

        if(path_dir[0] != '/')
        {
            char *new_path;

            new_path = add_path(path_dir, new_path);

            strcpy(path_dir, new_path);
            new_length = strlen(path_dir);

            free(new_path);
        }

        move_tree_create(path_dir, &tmp, new_length);

        if (times != 0)
        {
            incorrect_path = 0;
            times = 0;
            ret_res++;
        }
        incorrect_path = 0;

        if (ret_res == 0)
        {
            if (tmp->size == 0)
            {
                if (dir_first == 0)
                {
                    char** tmp_path = (char**)malloc(tmp->ch_amount * sizeof(char*));
                    for (int i = 0; i < tmp->ch_amount; i++)
                        tmp_path[i] = tmp->child[i]->name;

                    ch_amount = tmp->ch_amount;
                    sort_dir(tmp_path, ch_amount);

                    printf("%s:\n", copy_path);
                    for (int i = 0; i < tmp->ch_amount; i++)
                        printf("%s\n", tmp_path[i]);


                    strcpy(copy_path, "");
                }
                else
                {
                    char** tmp_path_dir = (char**)malloc(tmp->ch_amount * sizeof(char*));
                    char** tmp_path_file = (char**)malloc(tmp->ch_amount * sizeof(char*));

                    for (int i = 0; i< tmp->ch_amount; i ++)
                    {
                        if(tmp->child[i]->size == 0)
                            tmp_path_dir[dirs ++] = tmp->child[i]->name;
                        else
                            tmp_path_file[files ++] = tmp->child[i]->name;
                    }
                    sort_dir(tmp_path_dir, dirs);
                    sort_file(tmp_path_file, files);

                    printf("%s:\n", copy_path);
                    for (int i = 0; i < dirs; i++)
                        printf("%s\n", tmp_path_dir[i]);
                    for (int i = 0; i < files; i++)
                        printf("%s\n", tmp_path_file[i]);

           //         printf("\n");
                    files = 0;
                    dirs = 0;
                    strcpy(copy_path, "");
                    
                    for(int i = 0; i < dirs; i ++)
                      free(tmp_path_dir[i]);
      
                    free(tmp_path_dir);
    
                    for(int i = 0; i < files; i ++)
                      free(tmp_path_file[i]);
      
                    free(tmp_path_file);
                }
            }
    /*        else if(tmp->size == 0 && tmp->ch_amount == 0)
            {
                free(path_dir);
                free(tmp_dir);
                return 0;
            }*/
            else
                printf("%s\n", copy_path);
        }

    }
    
    
    
    if (ret_res != 0)
    {
        free(path_dir);
        free(tmp_dir);
        free(copy_path);
        ret_res = 0;
        return 0;
    }

    free(path_dir);
    free(tmp_dir);
    free(copy_path);
    return 1;
}
int create_dir(const char* path)
{
    int res_dir;
    if (exist == 1)
        res_dir = create_node(path);
    else
        res_dir = 0;

    return res_dir;
}
int create_file(const char* path, int file_size)
{
    int res_file;
    if (exist == 1)
        res_file = create_node(path, file_size);
    else
        res_file = 0;

    return res_file;
}

void setup_file_manager(file_manager_t* fm)
{
    fm->create = create;
    fm->create_dir = create_dir;
    fm->create_file = create_file;
    fm->change_dir = change_dir;
    fm->get_cur_dir = get_cur_dir;
    fm->remove = remove;
    fm->destroy = destroy;
    fm->list = list;
}

