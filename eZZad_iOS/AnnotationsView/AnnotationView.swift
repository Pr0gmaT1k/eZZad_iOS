//
//  AnnotationView.swift
//  eZZad_iOS
//
//  Created by AzerTy on 13/04/2017.
//  Copyright © 2017 Pr0gmaT1k. All rights reserved.
//

import UIKit
import Reusable
import MapKit

class AnnotationView: MKAnnotationView, NibLoadable {
  //
  // Mark:- IBOutlets
  @IBOutlet private weak var nameLabel: UILabel!
  
  //
  // Mark- Public func
  override func awakeFromNib() {
    super.awakeFromNib()
    self.frame = CGRect(x: 0, y: 0, width: 100, height: 54)
  }
  
  func setup(pointAnnotation: PointAnnotation) {
    self.annotation = pointAnnotation
    self.nameLabel.text = pointAnnotation.name
  }
}
