//
//  Annotation.swift
//  eZZad_iOS
//
//  Created by AzerTy on 13/04/2017.
//  Copyright © 2017 Pr0gmaT1k. All rights reserved.
//

import UIKit
import MapKit
import GEOSwift

class PointAnnotation: MKPointAnnotation {
  
  //
  // Mark:- Parsing key
  private enum PropertiesKey {
    static let name = "NOM"
    static let isHome = "MAISON"
    static let isCanteen = "CANTINE"
    static let isComOrga = "ORGA_COM"
    static let isInfirmary = "INFIRMERIE"
    static let isInfoPoint = "POINT_INFO"
    static let isPeasant = "PAYSANEXPU"
    static let isLocal = "LOC_EXPUL"
    static let isExpulsable = "NON_EXPUL"
    static let isMouvement = "MOUVEMENT"
  }
  
  private enum PropertiesValue {
    static let yes = "oui"
    static let no = "non"
  }
  
  //
  //Mark:- Properties
  var name: String?
  var isHome: Bool? = false
  var isCanteen: Bool? = false
  var isComOrga: Bool? = false
  var isInfirmary: Bool? = false
  var isInfoPoint: Bool? = false
  var isPeasant: Bool? = false
  var isLocal: Bool? = false
  var isExpulsable: Bool? = true
  var isMouvement: Bool? = false
  var placeIcon: UIImage? {
    switch true {
    case self.isInfirmary ?? false: return UIImage(named: "infirmary_icon")
    case self.isInfoPoint ?? false: return UIImage(named: "info_point_icon")
    case self.isCanteen ?? false: return UIImage(named: "info_point_icon")
    case self.isHome ?? false: return UIImage(named: "home_icon")
    default: return UIImage(named: "")
    }
  }
  
  //
  // Mark:- Public func
  init(waypoint: Waypoint) {
    super.init()
    self.coordinate = CLLocationCoordinate2DMake(waypoint.coordinate.y,
                                                 waypoint.coordinate.x)
    self.parse(waypoint: waypoint)
  }
  
  //
  // Mark:- Private func
  private func parse(waypoint: Waypoint) {
    guard let properties = waypoint.properties as? [String: Any] else { return }
    name = properties[PropertiesKey.name] as? String
    isHome = properties[PropertiesKey.isHome] as? String == PropertiesValue.yes
    isCanteen = properties[PropertiesKey.isCanteen] as? String == PropertiesValue.yes
    isComOrga = properties[PropertiesKey.isComOrga] as? String == PropertiesValue.yes
    isInfirmary = properties[PropertiesKey.isInfirmary] as? String == PropertiesValue.yes
    isInfoPoint = properties[PropertiesKey.isInfoPoint] as? String == PropertiesValue.yes
    isPeasant = properties[PropertiesKey.isPeasant] as? String == PropertiesValue.yes
    isLocal = properties[PropertiesKey.isLocal] as? String == PropertiesValue.yes
    isExpulsable = properties[PropertiesKey.isExpulsable] as? String == PropertiesValue.yes
    isMouvement = properties[PropertiesKey.isMouvement] as? String == PropertiesValue.yes
  }
}
