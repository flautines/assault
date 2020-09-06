#include "entity.h"

// --------------------------------------------------------------------------
Entity_t m_entities[MAX_ENTITIES];
u8 m_invalid;
Entity_t *m_next_free;
Entity_t *m_entities_end;

/////////////////////////////////////////////////////////////////////////////
// INIT
//
//
void manEntityInit() { 
  m_next_free = m_entities; 
  m_invalid = E_TYPE_INVALID;
  m_entities_end = m_entities + MAX_ENTITIES;
  cpct_memset(m_next_free, 0, sizeof(m_entities));
}
/////////////////////////////////////////////////////////////////////////////
// CREATE
//
//
Entity_t *manEntityCreate() {
  Entity_t *e = m_next_free;
  m_next_free = e + 1;
  e->type       = E_TYPE_DEFAULT;
  e->components = E_COMPONENT_DEFAULT;
  return e;
}
/////////////////////////////////////////////////////////////////////////////
// CLONE
//
//
Entity_t *manEntityClone(Entity_t *e_src) {
  Entity_t *e_clone = manEntityCreate();
  cpct_memcpy(e_clone, e_src, sizeof(Entity_t));
  return e_clone;
}

/////////////////////////////////////////////////////////////////////////////
// FOR ALL
//
//
void manEntityForAll(UpdateEntityFn_t fnUpdateEntity) {
  Entity_t *e = m_entities;
  while ( isValid(e) ) {
    fnUpdateEntity(e++);
  }
}
/////////////////////////////////////////////////////////////////////////////
// FOR ALL MATCHING
//
//
void manEntityForAllMatching(
    UpdateEntityFn_t fnUpdateEntity,
    u8               signature) 
{
  Entity_t *e = m_entities;  
  while ( isValid(e) ) {
    if ( signatureMatches(e, signature))
      fnUpdateEntity(e);
    e++;
  }
}
/////////////////////////////////////////////////////////////////////////////
// FOR ALL PAIRS MATCHING
//
//
void manEntityForAllPairsMatching(
  UpdateEntityPairsFn_t fnUpdatePairs, 
  u8                    signature)
{
  Entity_t *e_left = m_entities;
  while ( isValid(e_left) ) {
    if ( signatureMatches(e_left, signature) ) {
      Entity_t *e_right = e_left + 1;
      while ( isValid(e_right) ) {
        if ( signatureMatches(e_right, signature) ) {
          fnUpdatePairs(e_left, e_right);
        }
        ++e_right;
      }
    }
    ++e_left;
  }
}
/////////////////////////////////////////////////////////////////////////////
// DESTROY
//
//
// [E1][E4][E3][f][.][.]
void manEntityDestroy(Entity_t *e) {
  Entity_t *dead_e = e;
  --m_next_free;

  if (dead_e != m_next_free)
    cpct_memcpy(dead_e, m_next_free, sizeof(Entity_t));

  m_next_free->type = E_TYPE_INVALID;
}
/////////////////////////////////////////////////////////////////////////////
// DELETE
//
//
void manEntityDelete(Entity_t *e)
{
  e->type |= E_TYPE_DEAD;
}
/////////////////////////////////////////////////////////////////////////////
// UPDATE
//
//
void manEntityUpdate()
{
  Entity_t *e = m_entities;
  while (e->type != E_TYPE_INVALID) {
    if (e->type & E_TYPE_DEAD) {
      manEntityDestroy(e);
    } 
    else {
      ++e;
    }
  }
}
/////////////////////////////////////////////////////////////////////////////
// AVAILABLE
//
//
u8 manEntityAvailable()
{
  return (m_next_free < m_entities_end);
}
