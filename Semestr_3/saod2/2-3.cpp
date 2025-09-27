#include <algorithm>
#include <ctime>
#include <iostream>


struct tree {
  int data;
  tree *left;
  tree *right;
};

tree *addnode(tree *d, int key) {
  if (d == NULL) {
    d = new tree;
    d->data = key;
    d->left = NULL;
    d->right = NULL;
  } else if (key < d->data) {
    d->left = addnode(d->left, key);
  } else if (key > d->data) {
    d->right = addnode(d->right, key);
  }
  return d;
}

void LeftRight(tree *p) {
  if (p != NULL) {
    LeftRight(p->left);
    std::cout << p->data << " ";
    LeftRight(p->right);
  }
}
tree *ISDP(int mas[], int L, int R) {
  if (L > R) {
    return NULL;
  }

  int m = (L + R) / 2;
  tree *p = new tree;
  p->data = mas[m];
  p->left = ISDP(mas, L, m - 1);
  p->right = ISDP(mas, m + 1, R);
  return p;
}

tree *SDP1(tree *d, int key) {
  if (d == NULL) {
    d = new tree;
    d->data = key;
    d->left = NULL;
    d->right = NULL;
  } else if (key < d->data) {
    d->left = addnode(d->left, key);
  } else if (key > d->data) {
    d->right = addnode(d->right, key);
  }
  return d;
}

tree *SDP2(tree **root, int D) {
  tree **p = root;
  int check = 1;
  while ((*p != NULL) && (check == 1)) {
    if (D < (*p)->data) {
      p = &((*p)->left);
    } else if (D > (*p)->data) {
      p = &((*p)->right);
    } else {

      check = 0;
    }
  }
  if (*p == NULL) {
    *p = addnode(*p, D);
  }
}

int TreeSize(tree *p) {
  if (p == NULL)
    return 0;
  return 1 + TreeSize(p->left) + TreeSize(p->right);
}

int TreeLevel(tree *p) {
  if (p == NULL)
    return 0;
  return 1 + std::max(TreeLevel(p->left), TreeLevel(p->right));
}

int TreeSumma(tree *p) {
  if (p == NULL)
    return 0;
  return p->data + TreeSumma(p->left) + TreeSumma(p->right);
}

double sdp(tree *p, int l) {
  if (p == NULL)
    return 0;
  return l + sdp(p->left, l + 1) + sdp(p->right, l + 1);
}

double avgHeight(tree *p) {
  int size = TreeSize(p);
  if (size == 0)
    return 0;
  return sdp(p, 1) / size;
}

void deleteTree(tree *p) {
  if (p != NULL) {
    deleteTree(p->left);
    deleteTree(p->right);
    delete p;
  }
}

int main() {
  srand(time(NULL));
  int l = 0, n = 100;
  tree *rootrec = NULL;
  tree *rootdvoi = NULL;
  tree *rootISDP = NULL;
  int *mas = new int[100];
  int *arr = new int[100];
  std::cout << "MassivSort: ";
  for (int i = 0; i < 100; i++) {
    mas[i] = i + 1;
    arr[i] = mas[i];
    std::cout << mas[i] << " ";
  }
  std::cout << "\n" << std::endl;
  std::cout << "MassivNeSort: ";
  for (int i = 0; i < 100; i++) {
    std::swap(arr[i], arr[rand() % n]);
    std::cout << arr[i] << " ";
  }
  std::cout << "\n" << std::endl;
  for (int i = 0; i < 100; i++) {
    SDP2(&rootdvoi, arr[i]);
    rootrec = SDP1(rootrec, arr[i]);
  }

  std::cout << "\n" << std::endl;
  std::cout << "dvoinai kosvennosti: ";
  LeftRight(rootdvoi);
  std::cout << "\n" << std::endl;

  std::cout << "Rekursia: ";
  LeftRight(rootrec);
  std::cout << "\n" << std::endl;

  std::cout << "Sort: ";
  std::sort(arr, arr + n);
  for (int i = 0; i < 100; i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << "\n" << std::endl;

  rootISDP = ISDP(arr, 0, n - 1);
  std::cout << "ISDP: ";
  LeftRight(rootISDP);
  std::cout << "\n" << std::endl;
  int sizeDvoi = TreeSize(rootdvoi);
  int sumDvoi = TreeSumma(rootdvoi);
  int heightDvoi = TreeLevel(rootdvoi);
  double avgHeightDvoi = avgHeight(rootdvoi);

  int sizeRec = TreeSize(rootrec);
  int sumRec = TreeSumma(rootrec);
  int heightRec = TreeLevel(rootrec);
  double avgHeightRec = avgHeight(rootrec);

  int sizeISDP = TreeSize(rootISDP);
  int sumISDP = TreeSumma(rootISDP);
  int heightISDP = TreeLevel(rootISDP);
  double avgHeightISDP = avgHeight(rootISDP);

  std::cout << "Table:\n";
  std::cout << "_______________________________________\n";
  std::cout << "metod|\tsize|\tsumma|\tHigh|\tsrHigh |\n";
  std::cout << "_____|______|________|______|__________|\n";
  std::cout << "SDP2 |\t" << sizeDvoi << " |\t" << sumDvoi << " |\t"
            << heightDvoi << "  | \t" << avgHeightDvoi << "   |\n";
  std::cout << "_____|______|________|______|__________|\n";
  std::cout << "SDP1 |\t" << sizeRec << " |\t" << sumRec << " |\t" << heightRec
            << "  | \t" << avgHeightRec << "   |\n";
  std::cout << "_____|______|________|______|__________|\n";
  std::cout << "ISDP |\t" << sizeISDP << " |\t" << sumISDP << " |\t"
            << heightISDP << "   | \t" << avgHeightISDP << "    |\n";
  std::cout << "_____|______|________|______|__________|\n";

  return 0;
}