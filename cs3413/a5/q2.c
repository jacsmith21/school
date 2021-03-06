#include <stdio.h>
#include <stdlib.h>
#define SECTORS 100000

typedef struct Block {
  /**
   * The block #.
   */
  int block;

  /**
   * The next block in the file. -1 if this block is the last. -2 if this block is a free block.
   */
  int next;

  /**
   * The size of the file.
   */
  int size;

  /**
   * Which file this block belongs to! This is used to determine if a block has already been annotated.
   */
  int file;

  /**
   * Which block *this* block is in the sequence of blocks in a file. The first block in a file will get 0, the next
   * will get 1, etc.
   */
  int n;
} Block;

int DEBUG = 0;

int annotate(Block** blocks, Block* block, int file, int n) {
  block->n = n;
  block->file = file;

  if (block->next == -1) {
    block->size = n + 1;
  } else {
    block->size = annotate(blocks, blocks[block->next], file, n + 1);
  }

  return block->size;
}

/**
 *
 * @param blocks All of the blocks.
 * @param block The current block.
 * @param current_block The current block number.
 * @param total_moved The total moved blocks pointer. This will be incremented.
 */
void determine_moved(Block** blocks, Block* block, int current_block, int* total_moved) {
  int moved = current_block != block->block;
  if (moved) {
    (*total_moved)++;
  }

  int next_block = block->next == -1 ? -1 : current_block + 1;
  if (DEBUG) {
    if (moved) printf("%d %d [%d -> %d]\n", current_block, next_block, block->block, current_block);
    else printf("%d %d\n", current_block, next_block);
  } else printf("%d %d\n", current_block, next_block);

  if (block->next == -1) {
    return;
  }

  determine_moved(blocks, blocks[block->next], current_block + 1, total_moved);
}

int main() {
  // freopen("../disk_layout_simple_reversed.txt", "r", stdin); // Only use for testing

  // Steps
  // 1. Read blocks into array
  // 2. Count # of files and annotate each block with the file # and store the size in the starter block along with the
  // count of the block in the file (ie. first block in the file gets 0, second block gets 1, etc).
  // 3. Print out new disk layout using the information contained in the block array
  // 4. Iterate through the blocks and determine the new position of each block. If the current vs. new position
  // are different then increment moved blocks counter.

  Block* blocks[SECTORS];
  for (int i = 0; i < SECTORS; i++) {
    blocks[i] = NULL;
  }

  // Read the blocks!
  char* ptr = NULL;
  char* ptr1 = NULL;
  char *line = NULL;
  size_t line_size;
  int total = 0;
  while (getline(&line, &line_size, stdin) != -1) {
    int block = (int)strtol(line, &ptr, 10);
    int next = (int)strtol(ptr, &ptr1, 10);
    if (block < -0|| block > SECTORS) {
      printf("Found out-of-bounds block: %d", block);
      return 1;
    }

    if (next < -2 || next > SECTORS) {
      printf("Found out-of-bounds next block: %d", next);
      return 1;
    }

    blocks[total] = malloc(sizeof(Block));
    blocks[total]->next = next;
    blocks[total]->block = block; // block and total should be equal at this point
    blocks[total]->file = -1;
    blocks[total]->n = -1;
    blocks[total]->size = -1;
    total++;
  }

  if (DEBUG) printf("Read in %d blocks!\n", total);


  // ok this isn't exactly correct since files can start after we've already seen blocks in the file
  // In the disk_layout_simple_reversed we see this happen. Even though there are two files, we count three files
  // Since this value isn't really used other than to determine if we've seen a file it's ok
  int file_count = 0;

  // Start annotating
  for (int i = 0; i < total; i++) {
    Block* block = blocks[i];
    // Ignore free blocks and blocks that have already been annotated
    if (block->next == -2 || block->file != -1) {
      continue;
    }

    annotate(blocks, block, file_count, 0);
    file_count++;
  }

  if (DEBUG) printf("Found %d files!\n", file_count);

  int total_moved = 0;
  int current_block = 0;
  for (int i = 0; i < total; i++) {
    Block* block = blocks[i];
    // Ignore free blocks and blocks that aren't the start of a file
    if (block->next == -2 || block->n != 0) {
      continue;
    }


    determine_moved(blocks, block, current_block, &total_moved);
    current_block += block->size;
  }

  for (; current_block < total; current_block++) {
    printf("%d %d\n", current_block, -2);
  }

  printf("\nSummary\n");
  printf("Total blocks moved -> %d\n", total_moved);

  for (int i = 0; i < total; i++) {
    free(blocks[i]);
    blocks[i] = NULL;
  }
}
