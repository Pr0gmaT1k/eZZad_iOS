//
//  MBTileOverlay.swift
//  eZZad_iOS
//
//  Created by AzerTy on 13/03/2017.
//  Copyright © 2017 Pr0gmaT1k. All rights reserved.
//

import UIKit
import MapKit
import FMDB

class MBtilesOverlay : MKTileOverlay {
  let cache = NSCache<AnyObject, AnyObject>()
  let operationQueue = OperationQueue()
  private let query = "select tile_data from tiles where zoom_level = ? and tile_column = ? and tile_row = ?"
  private var dataBase: FMDatabase
  
  init(dbPath: String) {
    self.dataBase = FMDatabase(path: dbPath)
    super.init(urlTemplate: nil)
    if self.dataBase.open() == false {
      fatalError("DataBase file not found")
    }
  }
  
  
  override func url(forTilePath path: MKTileOverlayPath) -> URL {
    return URL(string: String(format: "http://tile.openstreetmap.org/%i/%i/%i.png", path.z, path.x, path.y))!
    
  }
  
  override func loadTile(at path: MKTileOverlayPath,
                         result: @escaping ((Data?, Error?) -> Void)) {
    result(tile(zoom: path.z, column: path.x, row: path.y), nil)
  }
  
  /*
   * :param: zoom The tile for the zoom level
   * :param: column The column of the map at this zoom level
   * :param: row The row of the map at this zoom level
   * :return: A tile image in NSData specified by the given area, nil if no such tile exists in the database
   */
  private func tile(zoom: Int, column: Int, row: Int) -> Data? {
    let finalRow = (2 ^^ zoom) - row - 1
    guard let resultSet = try? self.dataBase.executeQuery(query, values: [zoom, column, finalRow]) else { return nil }
    return resultSet.next() ? resultSet.data(forColumn: "tile_data") : nil
  }
}

/**
 * Swift interface for mbtiles database
 */
class MBTilesDBSwift {
  private let query = "select tile_data from tiles where zoom_level = ? and tile_column = ? and tile_row = ?"
  private var dataBase: FMDatabase
  
  init(dbPath: String) {
    self.dataBase = FMDatabase(path: dbPath)
    if self.dataBase.open() == false {
      fatalError("DataBase file not found")
    }
  }
  
  
}

precedencegroup PowerPrecedence { higherThan: MultiplicationPrecedence }
infix operator ^^ : PowerPrecedence
func ^^ (radix: Int, power: Int) -> Int {
  return Int(pow(Double(radix), Double(power)))
}
