# Output from the engine test

      ==============================
      Engine
      ==============================
      !!! 'Names' relation created

      !!! Tuples inserted into 'Names'

      !!! Showing 'Names'

      ===== SHOW Relation: Names
      [KEY] INTEGER ID: 1
            VARCHAR first_name: Bill
            VARCHAR last_name: Nye

      [KEY] INTEGER ID: 2
            VARCHAR first_name: Carll
            VARCHAR last_name: Sagan

      !!! Updated 'Names'. Set 'first_name' to 'Carl' on tupleID 1

      ===== SHOW Relation: Names
      [KEY] INTEGER ID: 1
            VARCHAR first_name: Bill
            VARCHAR last_name: Nye

      [KEY] INTEGER ID: 2
            VARCHAR first_name: Carl
            VARCHAR last_name: Sagan

      !!! Deleted tuple 0 from 'Names'

      ===== SHOW Relation: Names
      [KEY] INTEGER ID: 1
            VARCHAR first_name: Bill
            VARCHAR last_name: Nye

      !!! Created a 'other' relation (using Select) and added a tuple to this relation and 'names'

      ===== SHOW Relation: Names
      [KEY] INTEGER ID: 1
            VARCHAR first_name: Bill
            VARCHAR last_name: Nye

      [KEY] INTEGER ID: 4
            VARCHAR first_name: Neil
            VARCHAR last_name: Tyson

      ===== SHOW Relation: Other
      [KEY] INTEGER ID: 1
            VARCHAR first_name: Bill
            VARCHAR last_name: Nye

      [KEY] INTEGER ID: 2
            VARCHAR first_name: Carll
            VARCHAR last_name: Sagan

      !!! Computed union of 'Names' and 'Other'

      ===== SHOW Relation: Union of 'Names' and 'Other'
      [KEY] INTEGER ID: 1
            VARCHAR first_name: Bill
            VARCHAR last_name: Nye

      [KEY] INTEGER ID: 4
            VARCHAR first_name: Neil
            VARCHAR last_name: Tyson

      [KEY] INTEGER ID: 2
            VARCHAR first_name: Carll
            VARCHAR last_name: Sagan

      !!! Computed union of 'Names' and 'Other'

      ===== SHOW Relation: Difference of 'Names' and 'Other'
      [KEY] INTEGER ID: 4
            VARCHAR first_name: Neil
            VARCHAR last_name: Tyson

      !!! Computed product of 'Names' and 'Other'

      ===== SHOW Relation: Product of 'Names' and 'Other'
      [KEY] INTEGER Names.ID: 1
            VARCHAR Names.first_name: Bill
            VARCHAR Names.last_name: Nye
      [KEY] INTEGER Other.ID: 1
            VARCHAR Other.first_name: Bill
            VARCHAR Other.last_name: Nye

      [KEY] INTEGER Names.ID: 4
            VARCHAR Names.first_name: Neil
            VARCHAR Names.last_name: Tyson
      [KEY] INTEGER Other.ID: 1
            VARCHAR Other.first_name: Bill
            VARCHAR Other.last_name: Nye

      [KEY] INTEGER Names.ID: 1
            VARCHAR Names.first_name: Bill
            VARCHAR Names.last_name: Nye
      [KEY] INTEGER Other.ID: 2
            VARCHAR Other.first_name: Carll
            VARCHAR Other.last_name: Sagan

      [KEY] INTEGER Names.ID: 4
            VARCHAR Names.first_name: Neil
            VARCHAR Names.last_name: Tyson
      [KEY] INTEGER Other.ID: 2
            VARCHAR Other.first_name: Carll
            VARCHAR Other.last_name: Sagan

      !!! Computed Projection of 'Names'

      ===== SHOW Relation: Projection of 'Names'
            VARCHAR first_name: Bill

            VARCHAR first_name: Neil

      !!! Computed Renaming of 'Projection of 'Names''

      ===== SHOW Relation: Renaming of 'Projection of 'Names''
            VARCHAR first: Bill

            VARCHAR first: Neil

      !!! Exiting program...
