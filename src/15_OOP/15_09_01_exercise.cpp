// 15.31
// (a): Query(s1) | Query(s2) & ~ Query(s3)
// WordQuery s1 and s2 bind into a OrQuery,WordQuery s3 bind into a NotQuery,
// and bind the OrQuery and NotQuery into a AndQuery

// (b): Query(s1) | (Query(s2) & ~ Query(s3))
// 3 WordQuery, 1 OrQuery, 1 AndQuery, 1 NotQuery

// (c): (Query(s1) & Query(s2)) | (Query(s3) & Query(s4))
// 4 WordQuery, 2 AndQuery, 1 OrQuery

// ()